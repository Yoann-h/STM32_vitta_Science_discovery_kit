################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/file/file_mng.c 

OBJS += \
./modules/file/file_mng.o 

C_DEPS += \
./modules/file/file_mng.d 


# Each subdirectory must supply rules for building sources it contributes
modules/file/%.o modules/file/%.su modules/file/%.cyclo: ../modules/file/%.c modules/file/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/lcd" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/analogic" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/ultrasonic_sensor" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/rgb_led" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/servo" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/buzzer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/sdcard" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/rtc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/command" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/FreeRTOS-CLI" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/file" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-file

clean-modules-2f-file:
	-$(RM) ./modules/file/file_mng.cyclo ./modules/file/file_mng.d ./modules/file/file_mng.o ./modules/file/file_mng.su

.PHONY: clean-modules-2f-file

