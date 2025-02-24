/*
 * cli.h
 *
 *  Created on: Jul 17, 2024
 *      Author: Yoann Hervagault
 */

#ifndef COMMAND_CLI_H_
#define COMMAND_CLI_H_

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"
#include "FreeRTOS_CLI.h"
//#include "fatfs.h"
#include "usart.h"

#include "ws2813.h"
#include "buzzer.h"
#include "scores/scores.h"
#include "servo.h"

//#define BaseType_t uint32_t
extern osMutexId_t I2CMutexHandle;
void vCommandConsoleTask(void *pvParameters);
void vRegisterFileSystemCLICommands( void );

#endif /* COMMAND_CLI_H_ */
