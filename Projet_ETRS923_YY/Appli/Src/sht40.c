#include <stdio.h>
#include <string.h>
#include "sht40.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"   /* pdMS_TO_TICKS */

/* ========================================================================== */
/*  SHT40-AD1B  (Sensirion, I2C 0x44, commandes sur 1 octet, CRC-8 0x31)      */
/* ========================================================================== */

#define SHT40_CMD_MEASURE_HIGH   0xFDU   /* mesure haute precision (~8,3 ms) */
#define SHT40_CMD_SERIAL         0x89U
#define SHT40_CMD_SOFT_RESET     0x94U

static I2C_HandleTypeDef *sht40_hi2c;
static uint16_t           sht40_addr;

static uint8_t sht40_crc8(const uint8_t *data, uint8_t len)
{
	uint8_t crc = 0xFFU;
	for (uint8_t i = 0; i < len; i++) {
		crc ^= data[i];
		for (uint8_t b = 0; b < 8U; b++) {
			crc = (crc & 0x80U) ? (uint8_t)((crc << 1) ^ 0x31U) : (uint8_t)(crc << 1);
		}
	}
	return crc;
}

/* envoie une commande puis lit 6 octets (2 mots de 16 bits + CRC chacun) */
static int sht40_command_read6(uint8_t cmd, uint32_t wait_ms, uint8_t rx[6])
{
	if (HAL_I2C_Master_Transmit(sht40_hi2c, sht40_addr, &cmd, 1, I2C_TIMEOUT) != HAL_OK) {
		return -1;
	}
	osDelay(pdMS_TO_TICKS(wait_ms));
	if (HAL_I2C_Master_Receive(sht40_hi2c, sht40_addr, rx, 6, I2C_TIMEOUT) != HAL_OK) {
		return -2;
	}
	if ((sht40_crc8(&rx[0], 2) != rx[2]) || (sht40_crc8(&rx[3], 2) != rx[5])) {
		return -3;                              /* donnees corrompues */
	}
	return 0;
}

int16_t sht40_Init(I2C_HandleTypeDef *hi2c, uint16_t addr)
{
	sht40_hi2c = hi2c;
	sht40_addr = addr;

	uint8_t cmd = SHT40_CMD_SOFT_RESET;
	if (HAL_I2C_Master_Transmit(hi2c, addr, &cmd, 1, I2C_TIMEOUT) != HAL_OK) {
		return -1;                              /* pas de reponse a cette adresse */
	}
	osDelay(pdMS_TO_TICKS(2));                   /* 1 ms max apres un soft reset */

	uint8_t rx[6];
	int r = sht40_command_read6(SHT40_CMD_SERIAL, 2, rx);
	if (r < 0) {
		return (int16_t)(r - 10);
	}
	printf("SHT40 numero de serie: 0x%02X%02X%02X%02X\r\n", rx[0], rx[1], rx[3], rx[4]);
	return 0;
}

float sht40_GetHumidity(void)
{
	float sum = 0.0f;
	uint8_t good = 0U;

	for (int i = 0; i < SAMPLES_AMOUNT; i++) {
		uint8_t rx[6];
		if (sht40_command_read6(SHT40_CMD_MEASURE_HIGH, 10, rx) == 0) {
			uint16_t rh_ticks = (uint16_t)(((uint16_t)rx[3] << 8) | rx[4]);
			float rh = -6.0f + 125.0f * (float)rh_ticks / 65535.0f;
			if (rh < 0.0f)   { rh = 0.0f; }      /* la doc impose de borner a 0..100 %RH */
			if (rh > 100.0f) { rh = 100.0f; }
			printf("[sensors] Humidity: %f\r\n", rh);
			sum += rh;
			good++;
		}
		osDelay(pdMS_TO_TICKS(20));
	}

	if (good == 0U) {
		return NAN;
	}
	float avg = sum / (float)good;
	printf("[sensors] Average Humidity: %f\r\n", avg);
	return avg;
}
