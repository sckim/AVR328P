################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
777_Allfunction.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: 777_Allfunction.elf secondary-outputs

# Tool invocations
777_Allfunction.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,777_Allfunction.map -uvfprintf -mmcu=atmega328p -o "777_Allfunction.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

777_Allfunction.lss: 777_Allfunction.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 777_Allfunction.elf  >"777_Allfunction.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 777_Allfunction.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p 777_Allfunction.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 777_Allfunction.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
