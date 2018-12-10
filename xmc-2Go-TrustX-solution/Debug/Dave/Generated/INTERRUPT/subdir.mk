################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/INTERRUPT/interrupt.c \
../Dave/Generated/INTERRUPT/interrupt_conf.c 

OBJS += \
./Dave/Generated/INTERRUPT/interrupt.o \
./Dave/Generated/INTERRUPT/interrupt_conf.o 

C_DEPS += \
./Dave/Generated/INTERRUPT/interrupt.d \
./Dave/Generated/INTERRUPT/interrupt_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/INTERRUPT/%.o: ../Dave/Generated/INTERRUPT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1100_Q024x0064 -DNACK_CALLBACK_SUPPORT -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1100_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -I"$(PROJECT_LOC)/src/serial_io" -I"$(PROJECT_LOC)/src/cmd_process" -I"$(PROJECT_LOC)/Libraries/optiga-trust-x/optiga" -I"$(PROJECT_LOC)/Libraries/optiga-trust-x/optiga/include" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

