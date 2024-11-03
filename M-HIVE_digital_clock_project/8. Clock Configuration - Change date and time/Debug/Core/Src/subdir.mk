################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/7SEG.c \
../Core/Src/CLCD.c \
../Core/Src/button1_event.c \
../Core/Src/button2_event.c \
../Core/Src/button3_event.c \
../Core/Src/button4_event.c \
../Core/Src/buzzer.c \
../Core/Src/clock.c \
../Core/Src/clock_config.c \
../Core/Src/gpio.c \
../Core/Src/lap.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stopwatch.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/7SEG.o \
./Core/Src/CLCD.o \
./Core/Src/button1_event.o \
./Core/Src/button2_event.o \
./Core/Src/button3_event.o \
./Core/Src/button4_event.o \
./Core/Src/buzzer.o \
./Core/Src/clock.o \
./Core/Src/clock_config.o \
./Core/Src/gpio.o \
./Core/Src/lap.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stopwatch.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/7SEG.d \
./Core/Src/CLCD.d \
./Core/Src/button1_event.d \
./Core/Src/button2_event.d \
./Core/Src/button3_event.d \
./Core/Src/button4_event.d \
./Core/Src/buzzer.d \
./Core/Src/clock.d \
./Core/Src/clock_config.d \
./Core/Src/gpio.d \
./Core/Src/lap.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stopwatch.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/7SEG.d ./Core/Src/7SEG.o ./Core/Src/7SEG.su ./Core/Src/CLCD.d ./Core/Src/CLCD.o ./Core/Src/CLCD.su ./Core/Src/button1_event.d ./Core/Src/button1_event.o ./Core/Src/button1_event.su ./Core/Src/button2_event.d ./Core/Src/button2_event.o ./Core/Src/button2_event.su ./Core/Src/button3_event.d ./Core/Src/button3_event.o ./Core/Src/button3_event.su ./Core/Src/button4_event.d ./Core/Src/button4_event.o ./Core/Src/button4_event.su ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/clock.d ./Core/Src/clock.o ./Core/Src/clock.su ./Core/Src/clock_config.d ./Core/Src/clock_config.o ./Core/Src/clock_config.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/lap.d ./Core/Src/lap.o ./Core/Src/lap.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stopwatch.d ./Core/Src/stopwatch.o ./Core/Src/stopwatch.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

