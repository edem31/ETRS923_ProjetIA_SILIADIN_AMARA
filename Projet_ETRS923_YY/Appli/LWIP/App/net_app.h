#ifndef NET_APP_H
#define NET_APP_H

#include "lwip/netif.h"

/* A appeler UNE fois, depuis la tache qui possede LwIP (TaskComm), apres le demarrage
 * du scheduler : config RIF d'ETH1, lwip_init(), ajout de l'interface Ethernet, DHCP. */
void net_init(void);

/* A appeler en boucle, tres souvent (toutes les 1-2 ms) depuis cette MEME tache :
 * traite les trames recues, les timers LwIP, le lien Ethernet et le DHCP.
 * Ne jamais bloquer longtemps entre deux appels. */
void net_poll(void);

/* Interface reseau (pour ts_mqtt a l'etape suivante) */
struct netif *net_get_netif(void);

#endif /* NET_APP_H */
