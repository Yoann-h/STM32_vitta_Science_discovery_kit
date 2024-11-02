################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/buzzer/buzzer.c 

OBJS += \
./modules/buzzer/buzzer.o 

C_DEPS += \
./modules/buzzer/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
modules/buzzer/%.o modules/buzzer/%.su modules/buzzer/%.cyclo: ../modules/buzzer/%.c modules/buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/servo" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/buzzer" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/ds1307" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/hcsr04" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/ws2813" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/lcd16x2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-buzzer

clean-modules-2f-buzzer:
	-$(RM) ./modules/buzzer/buzzer.cyclo ./modules/buzzer/buzzer.d ./modules/buzzer/buzzer.o ./modules/buzzer/buzzer.su

.PHONY: clean-modules-2f-buzzer

