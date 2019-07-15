################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Allfunction.c \
../adc.c \
../gpio.c \
../lcd_lib.c \
../shiftOut.c \
../uart.c 

OBJS += \
./Allfunction.o \
./adc.o \
./gpio.o \
./lcd_lib.o \
./shiftOut.o \
./uart.o 

C_DEPS += \
./Allfunction.d \
./adc.d \
./gpio.d \
./lcd_lib.d \
./shiftOut.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


