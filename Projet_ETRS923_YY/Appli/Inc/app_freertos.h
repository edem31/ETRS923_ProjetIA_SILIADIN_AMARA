/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.h
  * Description        : FreeRTOS applicative header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Exported macro -------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */
extern osThreadId_t defaultTaskHandle;
extern osThreadId_t TaskSensorsHandle;
extern osThreadId_t TaskIAHandle;
extern osThreadId_t TaskCommHandle;
extern osMessageQueueId_t myQueue01Handle;

/* Exported function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
int16_t stts22h_Init(stmdev_ctx_t *stts22h_handle, I2C_HandleTypeDef *hi2c, uint16_t addr);
float stts22h_GetTemperature(stmdev_ctx_t *stts22h_handle);
int16_t lps22df_Init(stmdev_ctx_t *lps22df_handle, I2C_HandleTypeDef *hi2c, uint16_t addr);
float lps22df_GetPressure(stmdev_ctx_t *lps22df_handle);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTaskSensors(void *argument);
void StartTaskIA(void *argument);
void StartTaskComm(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

#ifdef __cplusplus
}
#endif
#endif /* __APP_FREERTOS_H */
