################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Allfunctions.cpp \
../PCF8574.cpp 

C_SRCS += \
../adc.c \
../gpio.c \
../i2c.c \
../lcd_lib.c \
../shiftOut.c \
../uart.c 

C_DEPS += \
./adc.d \
./gpio.d \
./i2c.d \
./lcd_lib.d \
./shiftOut.d \
./uart.d 

OBJS += \
./Allfunctions.o \
./PCF8574.o \
./adc.o \
./gpio.o \
./i2c.o \
./lcd_lib.o \
./shiftOut.o \
./uart.o 

CPP_DEPS += \
./Allfunctions.d \
./PCF8574.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


