################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/lcd1202/subdir.mk
-include src/chip8/subdir.mk
-include StdPeripheralDriver/src/subdir.mk
-include CMSIS/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
chip8_stm32_emul.hex \

SECONDARY_LIST += \
chip8_stm32_emul.lst \

SECONDARY_SIZE += \
chip8_stm32_emul.siz \


# All Target
all: chip8_stm32_emul.elf secondary-outputs

# Tool invocations
chip8_stm32_emul.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Linux GCC C Linker'
	arm-none-eabi-gcc -T"/home/sasha/work/MK/chip8-stm32/mcu/chip8_stm32_emul/stm32f100rb.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,chip8_stm32_emul.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"chip8_stm32_emul.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

chip8_stm32_emul.hex: chip8_stm32_emul.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex chip8_stm32_emul.elf "chip8_stm32_emul.hex"
	@echo 'Finished building: $@'
	@echo ' '

chip8_stm32_emul.lst: chip8_stm32_emul.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Create Listing'
	arm-none-eabi-objdump -h -S chip8_stm32_emul.elf >"chip8_stm32_emul.lst"
	@echo 'Finished building: $@'
	@echo ' '

chip8_stm32_emul.siz: chip8_stm32_emul.elf
	@echo 'Invoking: ARM Sourcery Linux GNU Print Size'
	arm-none-eabi-size  --format=berkeley chip8_stm32_emul.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) chip8_stm32_emul.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
