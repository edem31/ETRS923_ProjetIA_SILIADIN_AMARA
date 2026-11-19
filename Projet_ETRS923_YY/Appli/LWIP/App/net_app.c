/* Couche reseau : LwIP en mode NO_SYS=1, pilotee par UNE seule tache FreeRTOS (TaskComm).
 * Reprend ce que fait main.c de l'exemple LwIP_TCP_Echo_Server (RISAF_Config, Netif_Config,
 * boucle principale), sans toucher a main.c. */

#include <stdio.h>
#include "main.h"
#include "net_app.h"
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/dhcp.h"
#include "lwip/ip_addr.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "app_ethernet.h"

static struct netif gnetif;

/* Meme configuration RIF que l'exemple (ETH1 maitre + esclave : securise, privilegie).
 * Ecrase le SEC|NPRIV mis par SystemIsolation_Config() de main.c pour le maitre ETH1. */
static void net_rif_config(void)
{
  RIMC_MasterConfig_t rimc = {0};

  __HAL_RCC_RIFSC_CLK_ENABLE();

  rimc.MasterCID = RIF_CID_1;
  rimc.SecPriv   = RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV;
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_ETH1, &rimc);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_ETH1,
                                        RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
}

static void net_netif_config(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#if LWIP_DHCP
  ip_addr_set_zero_ip4(&ipaddr);
  ip_addr_set_zero_ip4(&netmask);
  ip_addr_set_zero_ip4(&gw);
#else
  IP4_ADDR(&ipaddr,  IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw,      GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#endif

  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
  netif_set_default(&gnetif);

  ethernet_link_status_updated(&gnetif);

#if LWIP_NETIF_LINK_CALLBACK
  netif_set_link_callback(&gnetif, ethernet_link_status_updated);
#endif
}

void net_init(void)
{
  printf("[net] initialisation Ethernet / LwIP ...\r\n");

  net_rif_config();
  lwip_init();
  net_netif_config();
}

void net_poll(void)
{
  /* Trames recues -> LwIP */
  ethernetif_input(&gnetif);

  /* Timers LwIP (ARP, DHCP, TCP...) */
  sys_check_timeouts();

#if LWIP_NETIF_LINK_CALLBACK
  Ethernet_Link_Periodic_Handle(&gnetif);
#endif

#if LWIP_DHCP
  DHCP_Periodic_Handle(&gnetif);
#endif
}

struct netif *net_get_netif(void)
{
  return &gnetif;
}
