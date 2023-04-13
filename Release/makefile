################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Service/TIME/subdir.mk
-include Service/JSON/subdir.mk
-include Service/COMM/subdir.mk
-include MCAL/WDT/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIM2/subdir.mk
-include MCAL/TIM1/subdir.mk
-include MCAL/TIM0/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/HR_OXIMETER/subdir.mk
-include HAL/HC/subdir.mk
-include HAL/FLASH/subdir.mk
-include HAL/BAT/subdir.mk
-include HAL/ADXL/subdir.mk
-include App/EMRG/subdir.mk
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

FLASH_IMAGE += \
SWIDRO_Final.hex \

EEPROM_IMAGE += \
SWIDRO_Final.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SWIDRO_Final.elf secondary-outputs

# Tool invocations
SWIDRO_Final.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SWIDRO_Final.map -mmcu=atmega328p -o "SWIDRO_Final.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SWIDRO_Final.lss: SWIDRO_Final.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SWIDRO_Final.elf  >"SWIDRO_Final.lss"
	@echo 'Finished building: $@'
	@echo ' '

SWIDRO_Final.hex: SWIDRO_Final.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SWIDRO_Final.elf  "SWIDRO_Final.hex"
	@echo 'Finished building: $@'
	@echo ' '

SWIDRO_Final.eep: SWIDRO_Final.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SWIDRO_Final.elf  "SWIDRO_Final.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SWIDRO_Final.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p SWIDRO_Final.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SWIDRO_Final.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
