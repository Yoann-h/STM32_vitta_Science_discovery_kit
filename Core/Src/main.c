/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "buzzer.h"
#include "ds1307.h"
#include "lcd16x2.h"
#include "hcsr04.h"
#include "servo.h"
#include "ws2813.h"
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

/* USER CODE BEGIN PV */
uint8_t strBuffer[40];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void buzzer_bip(ts_buzzer* buz);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM5_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  WS2813_HandlerTypeDef ledhandler;
  uint32_t ledBuffer[WS2813_DMA_BUFFER_SIZE];
  WS2813_eInit(&ledhandler, &htim2, ledBuffer);
  WS2813_eSetColor(&ledhandler,WS2813Orange,0);

  ts_lcd16x2 lcd;
  lcd.hi2c = &hi2c1;
  lcd.u8adress = LCD16x2_ADDRESS;
  lcd.u8col = 16;
  lcd.u8lines = 2;
  lcd.u8dotsize=1;
  elcd16x2_init(&lcd);
  sprintf((char*)strBuffer, "TEST LIGNE 1    ");
  elcd16x2_writeMsg(&lcd, strBuffer, strlen(strBuffer), 0, LCD16x2_LINE1);
  sprintf((char*)strBuffer, "TEST LIGNE 2    ");
  elcd16x2_writeMsg(&lcd, strBuffer, strlen(strBuffer), 0, LCD16x2_LINE2);
  HAL_Delay(10000);
  for(uint8_t i=0;i<100;i+=7)
  {
	  elcd16x2_DispLoading(&lcd, i);
	  HAL_Delay(1000);
  }

  ts_servo servo;
  servo_Init(&servo, &htim3, TIM_CHANNEL_2, 600,  2600, 0, 180 );
  servo_TestAmp(&servo, 1000);

  ts_hcsr04 ultrasonic_sensor;
  hcsr04_init(&ultrasonic_sensor, &htim8, GPIO_PIN_10, GPIOA);
  float hcsr04dist = hcsr04_getDistance(&ultrasonic_sensor);

  ts_buzzer buzzer;
  buzzer_eInit(&buzzer, &htim1, &htim5, TIM_CHANNEL_1);
  buzzer_bip(&buzzer);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */





//  int min_pwm=600; //us
//  int max_pwm=2600; //us
//  int pwm_value=min_pwm;
//  int step = 0;
  uint32_t Time_1Hz = HAL_GetTick();
  uint32_t Time_5Hz = HAL_GetTick();
  uint32_t Time_2Hz = HAL_GetTick();
  WS2813_eSetColor(&ledhandler,WS2813Off,0);
  uint8_t ledstate = 0;
  float fservoAngle = 0;
  uint8_t servodir = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if(HAL_GetTick()-Time_2Hz>=500)
	{
		Time_2Hz = HAL_GetTick();
		hcsr04dist = hcsr04_getDistance(&ultrasonic_sensor);
		sprintf((char*)strBuffer, "dist:%3.1fcm     ",hcsr04dist);
		elcd16x2_writeMsg(&lcd, strBuffer, strlen(strBuffer), 0, 0);
	}
	if(HAL_GetTick()-Time_5Hz>=200)
	{
		Time_5Hz = HAL_GetTick();
		servo_SetAngle(&servo,fservoAngle);
		if(servodir==0)
		{
			fservoAngle+=10;
		}
		else if(servodir==1)
		{
			fservoAngle-=10;
		}
		if(fservoAngle<=0)
		{
			servodir=0;
			fservoAngle=0;
		}
		if(fservoAngle>=180)
		{
			servodir=1;
			fservoAngle=180;
		}
	}
	if(HAL_GetTick()-Time_1Hz>=1000)
	{
		Time_1Hz = HAL_GetTick();
		if(ledstate==0)
		{
			WS2813_eSetColor(&ledhandler,WS2813Green,0);
			ledstate = 1;
		}
		else if(ledstate==1)
		{
			WS2813_eSetColor(&ledhandler,WS2813Off,0);
			ledstate = 0;
		}
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}

void buzzer_bip(ts_buzzer* buz)
{
	  buzzer_eStart(buz);
	  buzzer_eSetfrequency(buz,110*9);
	  HAL_Delay(200);
	  buzzer_eSetfrequency(buz,123.47*9);
	  HAL_Delay(200);
	  buzzer_eSetfrequency(buz,0);
	  buzzer_eStop(buz);
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
