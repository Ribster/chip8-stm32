################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lcd1202/lcd1202.c \
../src/lcd1202/utils.c 

OBJS += \
./src/lcd1202/lcd1202.o \
./src/lcd1202/utils.o 

C_DEPS += \
./src/lcd1202/lcd1202.d \
./src/lcd1202/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/lcd1202/%.o: ../src/lcd1202/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"/home/sasha/work/MK/chip8-stm32/mcu/chip8_stm32_emul/CMSIS" -I"/home/sasha/work/MK/chip8-stm32/mcu/chip8_stm32_emul/StdPeripheralDriver/inc" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


