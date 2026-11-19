/* Client MQTT ThingSpeak (port 1883, sans TLS) base sur l'appli MQTT de LwIP.
 * Mode NO_SYS=1 / API raw.
 * Necessite : src/apps/mqtt/mqtt.c dans le build, LWIP_DNS 1, LWIP_TCP 1,
 *             MEMP_NUM_SYS_TIMEOUT augmente de 1 (timer cyclique MQTT). */

#include <stdio.h>
#include <string.h>
#include "ts_mqtt.h"
#include "lwip/opt.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"
#include "lwip/dhcp.h"
#include "lwip/sys.h"

#define TS_CONNECT_TIMEOUT_MS  30000U
#define TS_RETRY_DELAY_MS       5000U

typedef enum { MQ_IDLE = 0, MQ_DNS, MQ_CONNECTING, MQ_CONNECTED } mq_state_t;

static mqtt_client_t *mq_client;
static mq_state_t     mq_state = MQ_IDLE;
static u32_t          mq_started_at;
static u32_t          mq_retry_at;
static u32_t          mq_session;            /* invalide les callbacks DNS tardifs */
static volatile ts_pub_status_t mq_pub_status = TS_PUB_IDLE;

static const struct mqtt_connect_client_info_t mq_info =
{
  .client_id   = TS_MQTT_CLIENT_ID,
  .client_user = TS_MQTT_USERNAME,
  .client_pass = TS_MQTT_PASSWORD,
  .keep_alive  = 60,      /* secondes ; la stack envoie les PINGREQ toute seule */
  .will_topic  = NULL     /* pas de "last will" */
};

static void mq_fail(const char *msg)
{
  if (msg != NULL)
  {
    printf("mqtt: %s\r\n", msg);
  }
  mq_state = MQ_IDLE;
  mq_retry_at = sys_now() + TS_RETRY_DELAY_MS;
}

static const char *mq_status_str(mqtt_connection_status_t s)
{
  switch (s)
  {
    case MQTT_CONNECT_ACCEPTED:                 return "accepte";
    case MQTT_CONNECT_DISCONNECTED:             return "deconnecte";
    case MQTT_CONNECT_TIMEOUT:                  return "timeout";
    case MQTT_CONNECT_REFUSED_PROTOCOL_VERSION: return "refuse (version protocole)";
    case MQTT_CONNECT_REFUSED_IDENTIFIER:       return "refuse (client id)";
    case MQTT_CONNECT_REFUSED_SERVER:           return "refuse (serveur)";
    case MQTT_CONNECT_REFUSED_USERNAME_PASS:    return "refuse (user/password)";
    case MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_:  return "refuse (non autorise)";
    default:                                    return "inconnu";
  }
}

static void mq_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
  LWIP_UNUSED_ARG(client);
  LWIP_UNUSED_ARG(arg);

  if (status == MQTT_CONNECT_ACCEPTED)
  {
    mq_state = MQ_CONNECTED;
    printf("mqtt: connecte au broker\r\n");
  }
  else
  {
    /* echec de connexion OU connexion perdue plus tard */
    printf("mqtt: %s\r\n", mq_status_str(status));
    mq_state = MQ_IDLE;
    mq_retry_at = sys_now() + TS_RETRY_DELAY_MS;
  }
}

static void mq_pub_cb(void *arg, err_t err)
{
  LWIP_UNUSED_ARG(arg);
  mq_pub_status = (err == ERR_OK) ? TS_PUB_OK : TS_PUB_ERROR;
  if (err != ERR_OK)
  {
    printf("mqtt: publication KO (err=%d)\r\n", (int)err);
  }
}

static void mq_start_connect(const ip_addr_t *ip)
{
  mq_state = MQ_CONNECTING;
  err_t e = mqtt_client_connect(mq_client, ip, TS_MQTT_PORT, mq_connection_cb, NULL, &mq_info);
  if (e != ERR_OK)
  {
    printf("mqtt: mqtt_client_connect err=%d\r\n", (int)e);
    mq_fail(NULL);
  }
}

static void mq_dns_cb(const char *name, const ip_addr_t *ipaddr, void *arg)
{
  LWIP_UNUSED_ARG(name);

  if (((u32_t)(uintptr_t)arg != mq_session) || (mq_state != MQ_DNS))
  {
    return; /* callback tardif d'une session abandonnee */
  }
  if (ipaddr == NULL)
  {
    mq_fail("DNS : nom non resolu");
    return;
  }
  printf("mqtt: %s = %s\r\n", TS_MQTT_HOST, ipaddr_ntoa(ipaddr));
  mq_start_connect(ipaddr);
}

/* Affiche ce que LwIP a recu du DHCP (utile pour comprendre un probleme de reseau) */
static void mq_print_netinfo(void)
{
  char a[20], b[20], c[20], d0[20], d1[20];
  struct netif *n = netif_default;
  if (n == NULL)
  {
    return;
  }
  const ip_addr_t *dns0 = dns_getserver(0);
  const ip_addr_t *dns1 = dns_getserver(1);
  ip4addr_ntoa_r(netif_ip4_addr(n),    a, sizeof(a));
  ip4addr_ntoa_r(netif_ip4_netmask(n), b, sizeof(b));
  ip4addr_ntoa_r(netif_ip4_gw(n),      c, sizeof(c));
  ipaddr_ntoa_r(dns0, d0, sizeof(d0));
  ipaddr_ntoa_r(dns1, d1, sizeof(d1));
  printf("mqtt: reseau ip=%s masque=%s passerelle=%s dns0=%s dns1=%s\r\n", a, b, c, d0, d1);

  /* Aucun serveur DNS recu du DHCP : on en met un public pour ne pas rester bloque */
  if (ip_addr_isany(dns0))
  {
    ip_addr_t pub;
    IP_ADDR4(&pub, 8, 8, 8, 8);
    dns_setserver(0, &pub);
    printf("mqtt: aucun DNS fourni par le DHCP -> utilisation de 8.8.8.8\r\n");
  }
}

static void mq_begin(void)
{
  if (mq_client == NULL)
  {
    mq_client = mqtt_client_new();
    if (mq_client == NULL)
    {
      mq_fail("mqtt_client_new KO (memoire)");
      return;
    }
  }

  mq_session++;
  mq_started_at = sys_now();
  mq_state = MQ_DNS;
  mq_print_netinfo();

#ifdef TS_MQTT_FORCE_IP
  {
    ip_addr_t forced;
    if (ipaddr_aton(TS_MQTT_FORCE_IP, &forced))
    {
      printf("mqtt: IP forcee %s (DNS ignore)\r\n", TS_MQTT_FORCE_IP);
      mq_start_connect(&forced);
      return;
    }
  }
#endif

  printf("mqtt: resolution DNS de %s ...\r\n", TS_MQTT_HOST);

  ip_addr_t ip;
  err_t e = dns_gethostbyname(TS_MQTT_HOST, &ip, mq_dns_cb, (void *)(uintptr_t)mq_session);
  if (e == ERR_OK)
  {
    /* deja en cache : le callback n'est PAS appele */
    printf("mqtt: %s = %s (cache)\r\n", TS_MQTT_HOST, ipaddr_ntoa(&ip));
    mq_start_connect(&ip);
  }
  else if (e != ERR_INPROGRESS)
  {
    mq_fail("dns_gethostbyname KO (LWIP_DNS ? serveur DNS ?)");
  }
}

void ts_mqtt_poll(struct netif *netif)
{
  u32_t now = sys_now();

  if (!dhcp_supplied_address(netif))
  {
    return;
  }

  switch (mq_state)
  {
    case MQ_IDLE:
      if ((s32_t)(now - mq_retry_at) >= 0)
      {
        mq_begin();
      }
      break;

    case MQ_DNS:
    case MQ_CONNECTING:
      if ((now - mq_started_at) > TS_CONNECT_TIMEOUT_MS)
      {
        /* on lit l'etat AVANT mqtt_disconnect() : il peut appeler le callback de connexion */
        const char *why = (mq_state == MQ_DNS)
            ? "timeout pendant la RESOLUTION DNS (pas de reponse du serveur DNS)"
            : "timeout pendant la CONNEXION TCP/MQTT (port 1883 bloque ? pas de reponse du broker)";
        if (mq_client != NULL)
        {
          mqtt_disconnect(mq_client);
        }
        mq_fail(why);
      }
      break;

    case MQ_CONNECTED:
    default:
      break;
  }
}

int ts_mqtt_connected(void)
{
  return (mq_state == MQ_CONNECTED) && (mq_client != NULL) && mqtt_client_is_connected(mq_client);
}

/* Ajoute "&fieldN=xx.yy" (ou "fieldN=xx.yy" pour le premier) dans buf. Retourne la nouvelle longueur.
 * Formatage manuel en centiemes : evite printf("%f") dans ce module. */
static int mq_append_field(char *buf, int len, int size, int field, float value, int first)
{
  int32_t c = (int32_t)(value * 100.0f + (value >= 0.0f ? 0.5f : -0.5f));
  const char *sign = (c < 0) ? "-" : "";
  if (c < 0) { c = -c; }

  int n = snprintf(buf + len, (size_t)(size - len), "%sfield%d=%s%ld.%02ld",
                   first ? "" : "&", field, sign, (long)(c / 100), (long)(c % 100));
  if ((n < 0) || (n >= (size - len)))
  {
    return -1;                                  /* buffer trop petit */
  }
  return len + n;
}

int ts_mqtt_publish_fields(const float values[], uint8_t count)
{
  if (!ts_mqtt_connected())
  {
    return -1;
  }

  char payload[96];
  int  len = 0;
  int  sent = 0;

  for (uint8_t i = 0; (i < count) && (i < 8U); i++)
  {
    if (values[i] != values[i])                 /* NAN : capteur absent ou mesure invalide */
    {
      continue;
    }
    len = mq_append_field(payload, len, (int)sizeof(payload), (int)i + 1, values[i], sent == 0);
    if (len < 0)
    {
      return -1;
    }
    sent++;
  }
  if (sent == 0)
  {
    printf("mqtt: rien a publier (toutes les valeurs sont invalides)\r\n");
    return -1;
  }

  char topic[40];
  snprintf(topic, sizeof(topic), "channels/%s/publish", TS_CHANNEL_ID);

  /* QoS 0, retain 0. Le payload est copie par la stack dans son tampon de sortie. */
  mq_pub_status = TS_PUB_PENDING;
  err_t e = mqtt_publish(mq_client, topic, payload, (u16_t)len, 0, 0, mq_pub_cb, NULL);
  if (e != ERR_OK)
  {
    printf("mqtt: mqtt_publish err=%d\r\n", (int)e);
    mq_pub_status = TS_PUB_ERROR;
    return -1;
  }
  printf("mqtt: publish %s -> %s\r\n", topic, payload);
  return 0;
}

ts_pub_status_t ts_mqtt_pub_status(void)
{
  return mq_pub_status;
}
