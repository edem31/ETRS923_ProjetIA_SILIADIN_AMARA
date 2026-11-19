#ifndef SHT40_H
#define SHT40_H

/* SHT40-AD1B (Sensirion) sur le bus I2C1 de l'IKS4A1 : pas de pilote ST, commandes I2C directes.
 * A appeler depuis une tache FreeRTOS (utilise osDelay). */

#include <math.h>
#include "main.h"

/* Adresse 7 bits 0x44 (variante AD1B) decalee pour le HAL */
#define SHT40_I2C_ADDR   (0x44U << 1)

/* Reset + lecture du numero de serie. Retourne 0 si le capteur repond, negatif sinon. */
int16_t sht40_Init(I2C_HandleTypeDef *hi2c, uint16_t addr);

/* Humidite relative moyenne sur SAMPLES_AMOUNT mesures, en %RH (0..100). NAN en cas d'erreur. */
float sht40_GetHumidity(void);

#endif /* SHT40_H */
