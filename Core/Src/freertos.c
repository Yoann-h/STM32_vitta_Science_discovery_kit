/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "scores/scores.h"
#include "lcd16x2.h"
#include "i2c.h"
#include "hcsr04.h"
#include "tim.h"
#include "ds1307.h"
#include "local_time_manager.h"
#include "sensor_config.h"
#include "display_manager.h"
#include "csv_logger_mng.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern ts_ltm LocalTime;
extern float fSensorValues[SensorCfg_sensorNb];
extern uint8_t u8EnableCSV;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for JukeboxTask */
osThreadId_t JukeboxTaskHandle;
const osThreadAttr_t JukeboxTask_attributes = {
  .name = "JukeboxTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for CommandTask */
osThreadId_t CommandTaskHandle;
const osThreadAttr_t CommandTask_attributes = {
  .name = "CommandTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SensorTask */
osThreadId_t SensorTaskHandle;
const osThreadAttr_t SensorTask_attributes = {
  .name = "SensorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LcdTask */
osThreadId_t LcdTaskHandle;
const osThreadAttr_t LcdTask_attributes = {
  .name = "LcdTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for I2CMutex */
osMutexId_t I2CMutexHandle;
const osMutexAttr_t I2CMutex_attributes = {
  .name = "I2CMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartJukeboxTask(void *argument);
void StartCommandTask(void *argument);
void StartLedTask(void *argument);
void StartSensorTask(void *argument);
void StartLCDMng(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of I2CMutex */
  I2CMutexHandle = osMutexNew(&I2CMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of JukeboxTask */
  JukeboxTaskHandle = osThreadNew(StartJukeboxTask, NULL, &JukeboxTask_attributes);

  /* creation of CommandTask */
  CommandTaskHandle = osThreadNew(StartCommandTask, NULL, &CommandTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(StartLedTask, NULL, &LedTask_attributes);

  /* creation of SensorTask */
  SensorTaskHandle = osThreadNew(StartSensorTask, NULL, &SensorTask_attributes);

  /* creation of LcdTask */
  LcdTaskHandle = osThreadNew(StartLCDMng, NULL, &LcdTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	uint8_t strBuffer[40];
	char datef[20];

//   float hcsr04dist = hcsr04_getDistance(&ultrasonic_sensor);

//	  lcd.hi2c = &hi2c1;
//	  lcd.u8adress = LCD16x2_ADDRESS;
//	  lcd.u8col = 16;
//	  lcd.u8lines = 2;
//	  lcd.u8dotsize=1;
//	  osMutexAcquire(I2CMutexHandle, 1000);
//	  elcd16x2_init(&lcd);
//	  osMutexRelease(I2CMutexHandle);
	  uint32_t Time_1Hz = HAL_GetTick();
	  float hcsr04dist= 0;
	  LtmRefLocalTime();


	ts_DataLog eData={eSensorList[SensorCfg_dist].header,eSensorList[SensorCfg_dist].unit,&fSensorValues[SensorCfg_dist],2};
	CSVLoggerMng_AddData(&eData);
	eData.pcDataName=eSensorList[SensorCfg_temp].header;
	eData.pcUnit    =eSensorList[SensorCfg_temp].unit;
	eData.pvDataVal=&fSensorValues[SensorCfg_temp];
	eData.u8Digitnb=0;
	CSVLoggerMng_AddData(&eData);
	eData.pcDataName=eSensorList[SensorCfg_lum].header;
	eData.pcUnit    =eSensorList[SensorCfg_lum].unit;
	eData.pvDataVal=&fSensorValues[SensorCfg_lum];
	eData.u8Digitnb=0;
	CSVLoggerMng_AddData(&eData);
	eData.pcDataName=eSensorList[SensorCfg_moist].header;
	eData.pcUnit    =eSensorList[SensorCfg_moist].unit;
	eData.pvDataVal=&fSensorValues[SensorCfg_moist];
	eData.u8Digitnb=1;
	CSVLoggerMng_AddData(&eData);
	CSVLoggerMng_Init(';', 1);
	uint32_t LastRecTime=0;
	uint32_t u32PeriodMs = 1000/iLogFrequency;


  /* Infinite loop */
  for(;;)
  {
	  if(u8EnableCSV==1 && (LocalTime.u32LocalTime-LastRecTime>=u32PeriodMs/1000))
	  {
		  LastRecTime = LocalTime.u32LocalTime;
		  CSVLoggerMng_Record();
	  }
		if(HAL_GetTick()-Time_1Hz>=1000)
		{
			Time_1Hz = HAL_GetTick();


//			sRTCDateTime dt;
//			ltm_UnixToDateTime(LocalTime.u32LocalTime, &dt);
//			dateFormat("dmy  H:i:s", dt, datef);
//			sprintf((char*)strBuffer, "dist:%3.1fcm     ",fSensorValues[SensorCfg_dist]);
//			osMutexAcquire(I2CMutexHandle, 100);
//			elcd16x2_writeMsg(&lcd, strBuffer, strlen(strBuffer), 0, LCD16x2_LINE1);
//			elcd16x2_writeMsg(&lcd, datef, strlen(datef), 0, LCD16x2_LINE2);
//			osMutexRelease(I2CMutexHandle);
		}
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartJukeboxTask */
/**
* @brief Function implementing the JukeboxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartJukeboxTask */
void StartJukeboxTask(void *argument)
{
  /* USER CODE BEGIN StartJukeboxTask */
  /* Infinite loop */
  for(;;)
  {
	  buzzer_vJukeBoxTask();
	  osDelay(1000);
  }
  /* USER CODE END StartJukeboxTask */
}

/* USER CODE BEGIN Header_StartCommandTask */
/**
* @brief Function implementing the CommandTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCommandTask */
void StartCommandTask(void *argument)
{
  /* USER CODE BEGIN StartCommandTask */
	vCommandConsoleTask(argument);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartCommandTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
* @brief Function implementing the LedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedTask */
void StartLedTask(void *argument)
{
  /* USER CODE BEGIN StartLedTask */
	WS2813_eProcess();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLedTask */
}

/* USER CODE BEGIN Header_StartSensorTask */
/**
* @brief Function implementing the SensorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorTask */
void StartSensorTask(void *argument)
{
  /* USER CODE BEGIN StartSensorTask */
	sensorCfg_eProcess();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartSensorTask */
}

/* USER CODE BEGIN Header_StartLCDMng */
/**
* @brief Function implementing the LcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCDMng */
void StartLCDMng(void *argument)
{
  /* USER CODE BEGIN StartLCDMng */
  DispMng_eProcess(&hi2c1);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDMng */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

