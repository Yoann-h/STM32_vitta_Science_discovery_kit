/*
 * sensor_config.c
 *
 *  Created on: Mar 5, 2025
 *      Author: yoyos
 */


#include <sensor_config.h>

float fSensorValues[SensorCfg_sensorNb];
volatile uint16_t adc_dma[anaSnrNB];

SensorCfg_Result eSensorCfgRefreshDist(ts_hcsr04 *hcsr04);
SensorCfg_Result eSensorCfgRefreshAna();

void init_analog_mng(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Start_DMA(hadc, (uint32_t *) adc_dma , anaSnrNB);
}

SensorCfg_Result eSensorCfgRefreshAna()
{
	SensorCfg_Result eRetVal = SensorCfg_OK;
	uint8_t FeMes=0;
	for(FeMes=0;FeMes<anaSnrNB;FeMes++ )
	{
		switch(FeMes){
			case anaTemperature:
				int B = 4275;
				float R = 4095.0/(adc_dma[FeMes])-1.0;
				fSensorValues[SensorCfg_temp] = 1.0/(log(R)/B+1/298.15)-273.15; //temperature °C
				break;
			case anaLight:
				fSensorValues[SensorCfg_lum]=(float)(4095-adc_dma[FeMes])*10/adc_dma[FeMes]; //light intensity
				//*FpResult = adc_dma_result[FeMes];
				break;
			case anaMoisture:
				fSensorValues[SensorCfg_moist]=((float)adc_dma[FeMes]/4095.0)*3.3; //sensor output in V
				break;
		}
	}
	return(eRetVal);
}

void sensorCfg_eProcess(void)
{
	ts_hcsr04 ultrasonic_sensor;
	hcsr04_init(&ultrasonic_sensor, &htim8, GPIO_PIN_10, GPIOA);
	init_analog_mng(&hadc1);
	uint32_t Time_2Hz = HAL_GetTick();
	while(1)
	{
		if(HAL_GetTick()-Time_2Hz>=500)
		{
			Time_2Hz = HAL_GetTick();
			fSensorValues[SensorCfg_dist] = hcsr04_getDistance(&ultrasonic_sensor);
			eSensorCfgRefreshAna();
		}
		osDelay(100);
	}
}
