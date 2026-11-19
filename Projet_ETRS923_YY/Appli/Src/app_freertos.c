/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "net_app.h"
#include "ts_mqtt.h"
#include "sht40.h"
#include "ia_pluie.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLAG_GO   0x01U
#define FLAG_DONE  0x02U

/* Envoi ThingSpeak (TaskComm) */
#define COMM_CONNECT_TIMEOUT_MS   20000U  /* attente max de la connexion MQTT */
#define COMM_PUBLISH_TIMEOUT_MS    5000U  /* attente max de la fin de publication */
#define COMM_MIN_INTERVAL_MS      15000U  /* limite ThingSpeak (compte gratuit) */
#define COMM_TEMP_MIN_C             -40.0f /* plage du STTS22H */
#define COMM_TEMP_MAX_C             125.0f
#define COMM_HUM_MIN_PCT              0.0f  /* plage du SHT40 */
#define COMM_HUM_MAX_PCT            100.0f
#define COMM_PRES_MIN_HPA           260.0f  /* plage du LPS22DF */
#define COMM_PRES_MAX_HPA          1260.0f
#define COMM_N_FIELDS                  6U   /* fields 1..6 ThingSpeak */

typedef enum { JOB_IDLE = 0, JOB_WAIT_CONNECT, JOB_WAIT_PUBLISH } comm_job_t;

typedef struct {
    float temperature;   /* degC -> field1 ThingSpeak */
    float humidity;      /* %RH  -> field2 ThingSpeak */
    float pressure;      /* hPa  -> field3 ThingSpeak */
} sensors_data_t;

static sensors_data_t SensorsData;
static ia_pluie_result_t IAResult;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
/* Definitions for TaskSensors */
osThreadId_t TaskSensorsHandle;
const osThreadAttr_t TaskSensors_attributes = {
  .name = "TaskSensors",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for TaskIA */
osThreadId_t TaskIAHandle;
const osThreadAttr_t TaskIA_attributes = {
  .name = "TaskIA",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for TaskComm */
osThreadId_t TaskCommHandle;
const osThreadAttr_t TaskComm_attributes = {
  .name = "TaskComm",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048 * 4
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static float comm_sanitize(float v, float lo, float hi, const char *name);

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TaskSensors */
  TaskSensorsHandle = osThreadNew(StartTaskSensors, NULL, &TaskSensors_attributes);

  /* creation of TaskIA */
  TaskIAHandle = osThreadNew(StartTaskIA, NULL, &TaskIA_attributes);

  /* creation of TaskComm */
  TaskCommHandle = osThreadNew(StartTaskComm, NULL, &TaskComm_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
	/* USER CODE BEGIN defaultTask */
	/* Infinite loop */
//	//B1 test
//	for (int i = 0; i < 20; i++) {
//		printf("B1=%d\r\n", HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
//		osDelay(500);
//	}
	for(;;)
	{
		/* 1. attendre l'appui sur B1 */
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) osDelay(20);
		osDelay(30);                                                    // anti-rebond
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) continue;   // faux contact

		printf("[def] appui detecte\r\n");
		osThreadFlagsSet(TaskSensorsHandle, FLAG_GO);
		osThreadFlagsWait(FLAG_DONE, osFlagsWaitAny, osWaitForever);
		printf("[def] cycle termine\r\n");

		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) osDelay(20);
		osDelay(30);
		printf("[def] pret pour un nouvel appui\r\n");
	}
	/* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_StartTaskSensors */
/**
 * @brief Function implementing the TaskSensors thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTaskSensors */
void StartTaskSensors(void *argument)
{
	/* USER CODE BEGIN TaskSensors */
	/*TODO
	 * LED green
	 * init i2c handler
	 * init sensors
	 * get values
	 * send event to start TaskIA with the latest sensors values
	 */
	extern I2C_HandleTypeDef hi2c;

	stmdev_ctx_t stts22h_handle = {0};
	int n = stts22h_Init(&stts22h_handle, &hi2c, STTS22H_I2C_ADD_H);
	if (n != 0xA0) {
		printf("[sensors] STTS22H absent (n=%d)\r\n", n);
	}

	stmdev_ctx_t lps22df_handle = {0};
		n = lps22df_Init(&lps22df_handle, &hi2c, LPS22DF_I2C_ADD_H);
		if (n != 0xB4) {
			printf("[sensors] lps22df absent (n=%d)\r\n", n);
		}
	uint8_t lps22df_ok = (n == 0xB4);

	/* SHT40-AD1B (humidite) */
	int16_t n_sht = sht40_Init(&hi2c, SHT40_I2C_ADDR);
	uint8_t sht40_ok = (n_sht == 0);
	if (!sht40_ok) {
		printf("SHT40 absent (n=%d)\r\n", n_sht);
	}

	//	float T = stts22h_GetTemperature(&stts22h_handle);
	//	printf("Temp = %f \r\n", T);

	/* Infinite loop */
	for(;;)
	{
		osThreadFlagsWait(FLAG_GO, osFlagsWaitAny, osWaitForever);      // attend B1

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET); //Green LED On

		SensorsData.temperature = stts22h_GetTemperature(&stts22h_handle);
		SensorsData.humidity = sht40_ok   ? sht40_GetHumidity()                  : NAN;
		SensorsData.pressure = lps22df_ok ? lps22df_GetPressure(&lps22df_handle) : NAN;
		osDelay(pdMS_TO_TICKS(500));

		printf("[sensors] Temperature = %f \r\n", SensorsData.temperature);
		printf("[sensors] Humidity = %f \r\n", SensorsData.humidity);
		printf("[sensors] Pressure = %f \r\n", SensorsData.pressure);

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);  //Green LED Off

		osThreadFlagsSet(TaskIAHandle, FLAG_GO);
	}
	/* USER CODE END TaskSensors */
}

/* USER CODE BEGIN Header_StartTaskIA */
/**
 * @brief Function implementing the TaskIA thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTaskIA */
void StartTaskIA(void *argument)
{
	/* USER CODE BEGIN TaskIA */
	/*TODO
	 * LED purple
	 * get latest values
	 * IA
	 * SEND event to taskComm to send data to the server
	 */
	/* Infinite loop */
	for(;;)
	{
		osThreadFlagsWait(FLAG_GO, osFlagsWaitAny, osWaitForever);        // wait ofr taskSensors to end

		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_RESET); //Red LED On

		//osDelay(pdMS_TO_TICKS(500));
		IAResult = ia_pluie_predire(SensorsData.temperature,
		                            SensorsData.humidity,
		                            SensorsData.pressure);

		if (IAResult.valide != 0U)
		{
			printf("[ia] pression station = %.1f hPa -> niveau mer = %.1f hPa\r\n",
			       SensorsData.pressure,
			       ia_pression_niveau_mer(SensorsData.pressure, IA_ALTITUDE_M));
				   
			printf("[ia] proba pluie = %d %% -> %s\r\n",
			       (int)(IAResult.proba * 100.0f),
			       (IAResult.pluie != 0U) ? "PLUIE" : "SEC");
		}
		else
		{
			printf("[ia] mesures invalides, pas de prediction\r\n");
		}


		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET); //Red LED On

		osThreadFlagsSet(TaskCommHandle, FLAG_GO);
	}
	/* USER CODE END TaskIA */
}

/* USER CODE BEGIN Header_StartTaskComm */
/**
 * @brief Function implementing the TaskComm thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTaskComm */
void StartTaskComm(void *argument)
{
	/* USER CODE BEGIN TaskComm */
	/* Cette tache est la SEULE a toucher a LwIP (NO_SYS=1) : elle fait tourner la pile en
	 * permanence. Le travail demande par TaskIA (FLAG_GO) est une petite machine a etats
	 * qui ne bloque jamais plus d'un tick, pour ne pas perdre de trames ni de timers LwIP. */
	comm_job_t job          = JOB_IDLE;
	uint32_t   job_started  = 0U;
	uint32_t   last_publish = 0U;
	uint8_t    has_published = 0U;
	/* field1 = temperature, field2 = humidite, field3 = pression,
	 * field4 = proba pluie (0..1), field5 = pluie (0/1), field6 = valide (0/1) */
	float      vals[COMM_N_FIELDS] = { NAN, NAN, NAN, NAN, NAN, NAN };

	net_init();

	/* Infinite loop */
	for(;;)
	{
		net_poll();
		ts_mqtt_poll(net_get_netif());      /* DNS, connexion et reconnexion MQTT */

		uint8_t finished = 0U;

		/* attend FLAG_GO au plus 1 tick, puis on repart servir LwIP */
		uint32_t flags = osThreadFlagsWait(FLAG_GO, osFlagsWaitAny, 1U);
		if (((flags & 0x80000000U) == 0U) && ((flags & FLAG_GO) != 0U) && (job == JOB_IDLE))
		{
			/* on fige les mesures du cycle (valeur invalide -> NAN -> field non envoye) */
			vals[0] = comm_sanitize(SensorsData.temperature, COMM_TEMP_MIN_C,   COMM_TEMP_MAX_C,   "temperature");
			vals[1] = comm_sanitize(SensorsData.humidity,    COMM_HUM_MIN_PCT,  COMM_HUM_MAX_PCT,  "humidite");
			vals[2] = comm_sanitize(SensorsData.pressure,    COMM_PRES_MIN_HPA, COMM_PRES_MAX_HPA, "pression");

			/* resultat de l'IA : proba et pluie n'ont de sens que si valide == 1,
			 * sinon NAN (field non envoye). Le field6 "valide" est toujours envoye. */
			vals[3] = (IAResult.valide != 0U) ? IAResult.proba            : NAN;
			vals[4] = (IAResult.valide != 0U) ? (float)IAResult.pluie     : NAN;
			vals[5] = (float)IAResult.valide;

			if ((has_published != 0U) && ((HAL_GetTick() - last_publish) < COMM_MIN_INTERVAL_MS))
			{
				printf("[comm] envoi ignore : ThingSpeak limite a 1 mise a jour / 15 s\r\n");
				finished = 1U;
			}
			else
			{
				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET); //Blue LED On
				job_started = HAL_GetTick();
				job = JOB_WAIT_CONNECT;
			}
		}

		uint32_t elapsed = HAL_GetTick() - job_started;

		switch (job)
		{
		case JOB_WAIT_CONNECT:
			if (ts_mqtt_connected() != 0)
			{
				if (ts_mqtt_publish_fields(vals, COMM_N_FIELDS) == 0)
				{
					job_started = HAL_GetTick();
					job = JOB_WAIT_PUBLISH;
				}
				else
				{
					printf("[comm] publication refusee\r\n");
					finished = 1U;
				}
			}
			else if (elapsed > COMM_CONNECT_TIMEOUT_MS)
			{
				printf("[comm] pas de connexion MQTT (timeout)\r\n");
				finished = 1U;
			}
			break;

		case JOB_WAIT_PUBLISH:
			if (ts_mqtt_pub_status() == TS_PUB_OK)
			{
				has_published = 1U;
				last_publish = HAL_GetTick();
				printf("[comm] mesures envoyees a ThingSpeak\r\n");
				finished = 1U;
			}
			else if (ts_mqtt_pub_status() == TS_PUB_ERROR)
			{
				printf("[comm] echec de la publication\r\n");
				finished = 1U;
			}
			else if (elapsed > COMM_PUBLISH_TIMEOUT_MS)
			{
				printf("[comm] publication : timeout\r\n");
				finished = 1U;
			}
			break;

		default:
			break;
		}

		if (finished != 0U)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET); //Blue LED Off
			job = JOB_IDLE;
			osThreadFlagsSet(defaultTaskHandle, FLAG_DONE);
		}
	}
	/* USER CODE END TaskComm */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint16_t           addr;   // adresse 8 bits (déjà décalée)
} sensor_bus_t;

static sensor_bus_t stts22h_bus;
static sensor_bus_t lps22df_bus;

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
	sensor_bus_t *bus = (sensor_bus_t *)handle;
	return (HAL_I2C_Mem_Read(bus->hi2c, bus->addr, reg,
			I2C_MEMADD_SIZE_8BIT, buf, len, I2C_TIMEOUT) == HAL_OK) ? 0 : -1;
}

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *buf, uint16_t len)
{
	sensor_bus_t *bus = (sensor_bus_t *)handle;
	return (HAL_I2C_Mem_Write(bus->hi2c, bus->addr, reg,
			I2C_MEMADD_SIZE_8BIT, (uint8_t *)buf, len, I2C_TIMEOUT) == HAL_OK) ? 0 : -1;
}

int16_t stts22h_Init(stmdev_ctx_t *stts22h_handle, I2C_HandleTypeDef *hi2c, uint16_t addr){
	//wrapper for I2C read

	stts22h_bus.hi2c = hi2c;
	stts22h_bus.addr = addr;

	stts22h_handle->read_reg  = platform_read;
	stts22h_handle->write_reg = platform_write;
	stts22h_handle->handle = &stts22h_bus;
	//init sensor struct done

	uint8_t stts22h_id;
	int n = stts22h_dev_id_get(stts22h_handle, &stts22h_id);
	if (n<0){
		return n;
	}
	else{
		return stts22h_id;
	}
}

float stts22h_GetTemperature(stmdev_ctx_t *stts22h_handle){

	stts22h_odr_temp_t odr;
	stts22h_temp_data_rate_get(stts22h_handle, &odr);
//	printf("data rate %d\r\n",odr);
	int n = stts22h_temp_data_rate_set(stts22h_handle, STTS22H_25Hz);

	n = stts22h_temp_data_rate_get(stts22h_handle, &odr);
//	printf("data rate %d\r\n",odr);

	int16_t rawTemp;
	float Temp;
	float averageTemp = 0;



	for (int i=0; i<SAMPLES_AMOUNT; i++){
		osDelay(pdMS_TO_TICKS(50));
		n = stts22h_temperature_raw_get(stts22h_handle, &rawTemp);
		Temp = stts22h_from_lsb_to_celsius(rawTemp);
		averageTemp += Temp;
		printf("[sensors] Temperature: %f\r\n", Temp);
	}

	averageTemp /= SAMPLES_AMOUNT;

	printf("[sensors] Average Temperature: %f\r\n", averageTemp);

	if (n<0){
		return n;
	}

	return averageTemp;
}

int16_t lps22df_Init(stmdev_ctx_t *lps22df_handle, I2C_HandleTypeDef *hi2c, uint16_t addr){
	//wrapper for I2C read

	lps22df_bus.hi2c = hi2c;
	lps22df_bus.addr = addr;

	lps22df_handle->read_reg  = platform_read;
	lps22df_handle->write_reg = platform_write;
	lps22df_handle->handle = &lps22df_bus;
	//init sensor struct done

	lps22df_id_t lps22df_id;
	int n = lps22df_id_get(lps22df_handle, &lps22df_id);
	if (n<0){
		return n;
	}
	else{
		return lps22df_id.whoami;
	}
}

float lps22df_GetPressure(stmdev_ctx_t *lps22df_handle){

	lps22df_md_t lps22df_mode;
	lps22df_mode_get(lps22df_handle, &lps22df_mode);
//	printf("data rate %d\r\n",lps22df_mode.odr);
	lps22df_mode.odr = LPS22DF_10Hz;
	int n = lps22df_mode_set(lps22df_handle, &lps22df_mode);

	lps22df_mode_get(lps22df_handle, &lps22df_mode);
//	printf("data rate %d\r\n",lps22df_mode.odr);

	float Pressure;
	float averagePressure = 0;

	lps22df_data_t lps22df_data;


	for (int i=0; i<SAMPLES_AMOUNT; i++){
		//check if the sensor is ready
		lps22df_all_sources_t src;
		src.drdy_pres = 0;
		for (int t = 0; (t < 30) && (src.drdy_pres == 0); t++){
			n = lps22df_all_sources_get(lps22df_handle, &src);
			if (n<0){
				return NAN;
			}
			if (src.drdy_pres == 0){
				osDelay(pdMS_TO_TICKS(10));
			}
		}
		if (src.drdy_pres == 0){
			return NAN;
		}

		n = lps22df_data_get(lps22df_handle, &lps22df_data);
		if (n<0){
			return NAN;
		}
		Pressure = lps22df_data.pressure.hpa;
		averagePressure += Pressure;
		printf("[sensors] Pressure: %f\r\n", Pressure);
	}

	averagePressure /= SAMPLES_AMOUNT;

	printf("[sensors] Average Pressure: %f\r\n", averagePressure);

	return averagePressure;
}
/* Renvoie v si elle est dans [lo, hi], sinon NAN (le field correspondant ne sera pas envoye) */
static float comm_sanitize(float v, float lo, float hi, const char *name)
{
	if ((v != v) || (v < lo) || (v > hi))
	{
		printf("[comm] %s invalide : field non envoye\r\n", name);
		return NAN;
	}
	return v;
}
/* USER CODE END Application */

