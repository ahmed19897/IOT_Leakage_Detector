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
FLASH_IMAGE += \
USART.hex \

EEPROM_IMAGE += \
USART.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: USART.elf secondary-outputs

# Tool invocations
USART.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,USART.map -mmcu=atmega32 -o "USART.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

USART.hex: USART.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex USART.elf  "USART.hex"
	@echo 'Finished building: $@'
	@echo ' '

USART.eep: USART.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex USART.elf  "USART.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: USART.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 USART.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: USART.elf
	@echo 'Invoking: AVRDude'
	D:\Engineering\IMT\03-ARM Course\IMT_ARM_Course\IMT_ARM_Course\02- Tools\03- IMT SDK\IMT_SDK_Win_64\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -u -Uflash:w:USART.hex:a -Ulfuse:w:0xc4:m -Uhfuse:w:0xd9:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(C_DEPS) USART.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
