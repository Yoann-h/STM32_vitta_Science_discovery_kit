################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/sdcard/user_diskio_spi.c 

OBJS += \
./modules/sdcard/user_diskio_spi.o 

C_DEPS += \
./modules/sdcard/user_diskio_spi.d 


# Each subdirectory must supply rules for building sources it contributes
modules/sdcard/%.o modules/sdcard/%.su modules/sdcard/%.cyclo: ../modules/sdcard/%.c modules/sdcard/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/lcd" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/analogic" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/ultrasonic_sensor" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/rgb_led" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/servo" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/buzzer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/sdcard" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/rtc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/command" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/FreeRTOS-CLI" -I"C:/Users/yoyos/Desktop/projets/devstm32/STM32_Starterkit_vitta_science/vita_science_kit/modules/file" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-sdcard

clean-modules-2f-sdcard:
	-$(RM) ./modules/sdcard/user_diskio_spi.cyclo ./modules/sdcard/user_diskio_spi.d ./modules/sdcard/user_diskio_spi.o ./modules/sdcard/user_diskio_spi.su

.PHONY: clean-modules-2f-sdcard

