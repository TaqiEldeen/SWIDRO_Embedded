################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/FLASH/FLASH_prg.c 

OBJS += \
./HAL/FLASH/FLASH_prg.o 

C_DEPS += \
./HAL/FLASH/FLASH_prg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/FLASH/%.o: ../HAL/FLASH/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


