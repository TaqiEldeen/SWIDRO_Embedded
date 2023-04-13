################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/HR_OXIMETER/subdir.mk
-include HAL/HC/subdir.mk
-include HAL/ADXL/subdir.mk
-include App/subdir.mk
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
SWIDRO_Final.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: SWIDRO_Final.elf secondary-outputs

# Tool invocations
SWIDRO_Final.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SWIDRO_Final.map -mmcu=atmega32 -o "SWIDRO_Final.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SWIDRO_Final.lss: SWIDRO_Final.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SWIDRO_Final.elf  >"SWIDRO_Final.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SWIDRO_Final.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SWIDRO_Final.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SWIDRO_Final.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
