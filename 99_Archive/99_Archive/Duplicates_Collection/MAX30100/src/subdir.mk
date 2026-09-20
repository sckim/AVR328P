################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
E:\Eclipse4Arduino\arduinoPlugin\libraries\MAX30100\1.0.0\src\MAX30100.cpp 

LINK_OBJ += \
.\libraries\MAX30100\src\MAX30100.cpp.o 

CPP_DEPS += \
.\libraries\MAX30100\src\MAX30100.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\MAX30100\src\MAX30100.cpp.o: E:\Eclipse4Arduino\arduinoPlugin\libraries\MAX30100\1.0.0\src\MAX30100.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:\Eclipse4Arduino\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"E:\Eclipse4Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\cores\arduino" -I"E:\Eclipse4Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\variants\standard" -I"E:\Eclipse4Arduino\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src" -I"E:\Eclipse4Arduino\arduinoPlugin\libraries\MAX30100\1.0.0\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


