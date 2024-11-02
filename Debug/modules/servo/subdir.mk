################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/servo/servo.c 

OBJS += \
./modules/servo/servo.o 

C_DEPS += \
./modules/servo/servo.d 


# Each subdirectory must supply rules for building sources it contributes
modules/servo/%.o modules/servo/%.su modules/servo/%.cyclo: ../modules/servo/%.c modules/servo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/servo" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/buzzer" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/ds1307" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/hcsr04" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/ws2813" -I"C:/Users/yoyos/STM32CubeIDE/workspace_github/vita_science_kit_v2/modules/lcd16x2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-servo

clean-modules-2f-servo:
	-$(RM) ./modules/servo/servo.cyclo ./modules/servo/servo.d ./modules/servo/servo.o ./modules/servo/servo.su

.PHONY: clean-modules-2f-servo

