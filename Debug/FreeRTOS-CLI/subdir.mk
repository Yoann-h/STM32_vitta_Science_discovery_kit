################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS-CLI/FreeRTOS_CLI.c 

OBJS += \
./FreeRTOS-CLI/FreeRTOS_CLI.o 

C_DEPS += \
./FreeRTOS-CLI/FreeRTOS_CLI.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-CLI/%.o FreeRTOS-CLI/%.su FreeRTOS-CLI/%.cyclo: ../FreeRTOS-CLI/%.c FreeRTOS-CLI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/FreeRTOS-CLI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2d-CLI

clean-FreeRTOS-2d-CLI:
	-$(RM) ./FreeRTOS-CLI/FreeRTOS_CLI.cyclo ./FreeRTOS-CLI/FreeRTOS_CLI.d ./FreeRTOS-CLI/FreeRTOS_CLI.o ./FreeRTOS-CLI/FreeRTOS_CLI.su

.PHONY: clean-FreeRTOS-2d-CLI

