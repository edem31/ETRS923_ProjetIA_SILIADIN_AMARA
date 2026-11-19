#ifndef TS_MQTT_H
#define TS_MQTT_H

#include "lwip/netif.h"

/* Identifiants ThingSpeak : dans ts_secrets.h (NON versionne, voir ts_secrets.example.h) */
#include "ts_secrets.h"

#define TS_MQTT_HOST         "mqtt3.thingspeak.com"
#define TS_MQTT_PORT         1883

/* DIAGNOSTIC : decommente pour IGNORER le DNS et se connecter directement a cette IP
 * (celle de mqtt3.thingspeak.com, affichee dans les logs quand le DNS marche).
 *  - ca se connecte avec l'IP forcee  -> le probleme est le DNS du reseau
 *  - ca ne se connecte pas non plus   -> le port 1883 (TCP) est bloque / filtre */
/* #define TS_MQTT_FORCE_IP   "18.207.44.162" */

typedef enum
{
  TS_PUB_IDLE = 0,   /* aucune publication depuis le dernier appel */
  TS_PUB_PENDING,    /* publication demandee, pas encore ecrite sur la socket */
  TS_PUB_OK,         /* publication envoyee */
  TS_PUB_ERROR       /* publication en erreur */
} ts_pub_status_t;

/* A appeler a chaque tour de la boucle de la tache reseau (NO_SYS=1) :
 * DNS, connexion au broker, reconnexion automatique, timeouts. */
void ts_mqtt_poll(struct netif *netif);

/* 1 si connecte au broker et pret a publier */
int  ts_mqtt_connected(void);

/* Publie plusieurs valeurs d'un coup (QoS 0) : values[0] -> field1, values[1] -> field2, etc.
 * Une valeur NAN est omise (le field correspondant n'est pas mis a jour).
 * 0 = demande acceptee par la stack, -1 = refusee (pas connecte, ou toutes les valeurs sont NAN).
 * Le resultat final se lit avec ts_mqtt_pub_status().
 * ThingSpeak : 15 s minimum entre deux publications, 8 fields au maximum. */
int  ts_mqtt_publish_fields(const float values[], uint8_t count);

ts_pub_status_t ts_mqtt_pub_status(void);

#endif /* TS_MQTT_H */
