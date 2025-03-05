/*
 * sensor_config.h
 *
 *  Created on: Mar 5, 2025
 *      Author: yoyos
 */

#ifndef INC_SENSOR_CONFIG_H_
#define INC_SENSOR_CONFIG_H_

#include "hcsr04.h"
#include "adc.h"
#include "tim.h"

extern ADC_HandleTypeDef hadc1;

typedef enum {
	SensorCfg_OK, SensorCfg_PARAMETER_ERROR, SensorCfg_INTERNAL_ERROR, SensorCfg_RESULTNB
} SensorCfg_Result;

typedef enum {
	SensorCfg_dist, SensorCfg_lum, SensorCfg_moist, SensorCfg_temp, SensorCfg_sensorNb
} SensorList;

typedef enum
{
	anaTemperature = 0,
	anaLight,
	anaMoisture,
	anaSnrNB
} eSensorAnalog;

typedef struct {
	char* header;
	char* lcdStr;
	char* unit;
} SensorStr;

static SensorStr eSensorList[SensorCfg_sensorNb]={
		{"Distance", "dist","cm"},
		{"Luminosity","lum","V"},
		{"Humidity","hty",""},
		{"Temperature","temp","dC"}
};

void sensorCfg_eProcess(void);

#endif /* INC_SENSOR_CONFIG_H_ */
