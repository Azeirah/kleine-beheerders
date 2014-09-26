################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/UC-Week3-IR-Interrupts.c \
../src/cr_startup_lpc13xx.c \
../src/crp.c \
../src/infrared.c \
../src/leds.c \
../src/timer.c 

OBJS += \
./src/UC-Week3-IR-Interrupts.o \
./src/cr_startup_lpc13xx.o \
./src/crp.o \
./src/infrared.o \
./src/leds.o \
./src/timer.o 

C_DEPS += \
./src/UC-Week3-IR-Interrupts.d \
./src/cr_startup_lpc13xx.d \
./src/crp.d \
./src/infrared.d \
./src/leds.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c99 -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC13XX__ -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


