################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/serial_io/subdir.mk
-include src/cmd_process/subdir.mk
-include Startup/subdir.mk
-include Libraries/optiga-trust-x/pal/xmc_dave/subdir.mk
-include Libraries/optiga-trust-x/optiga/util/subdir.mk
-include Libraries/optiga-trust-x/optiga/dtls/subdir.mk
-include Libraries/optiga-trust-x/optiga/crypt/subdir.mk
-include Libraries/optiga-trust-x/optiga/comms/ifx_i2c/subdir.mk
-include Libraries/optiga-trust-x/optiga/comms/subdir.mk
-include Libraries/optiga-trust-x/optiga/common/subdir.mk
-include Libraries/optiga-trust-x/optiga/cmd/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/UART/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/I2C_MASTER/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC1/subdir.mk
-include Dave/Generated/CLOCK_XMC1/subdir.mk
-include Dave/Generated/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
SECONDARY_FLASH += \
xmc2go-TrustX.hex \

SECONDARY_LIST += \
xmc2go-TrustX.lst \

SECONDARY_SIZE += \
xmc2go-TrustX.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "xmc2go-TrustX.map"

TOOLCHAIN_ROOT=C:/DAVE_4-4-2_64bit/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/Workspace/DAVE-4.4.2-64Bit/Temp/xmc2go-TrustX

# All Target
all: xmc2go-TrustX.elf secondary-outputs

# Tool invocations
xmc2go-TrustX.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "xmc2go-TrustX.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
xmc2go-TrustX.hex: xmc2go-TrustX.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "xmc2go-TrustX.elf" "xmc2go-TrustX.hex"
	@echo 'Finished building: $@'
	@echo.
xmc2go-TrustX.lst: xmc2go-TrustX.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "xmc2go-TrustX.elf" > "xmc2go-TrustX.lst"
	@echo 'Finished building: $@'
	@echo.
xmc2go-TrustX.siz: xmc2go-TrustX.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "xmc2go-TrustX.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/CLOCK_XMC1/clock_xmc1.o Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.o Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1.o Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/I2C_MASTER/i2c_master.o Dave/Generated/I2C_MASTER/i2c_master_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Dave/Generated/UART/uart.o Dave/Generated/UART/uart_conf.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc1_eru.o Libraries/XMCLib/src/xmc1_flash.o Libraries/XMCLib/src/xmc1_gpio.o Libraries/XMCLib/src/xmc1_rtc.o Libraries/XMCLib/src/xmc1_scu.o Libraries/XMCLib/src/xmc_acmp.o Libraries/XMCLib/src/xmc_bccu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_math.o Libraries/XMCLib/src/xmc_pau.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_prng.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Libraries/optiga-trust-x/optiga/cmd/CommandLib.o Libraries/optiga-trust-x/optiga/common/Logger.o Libraries/optiga-trust-x/optiga/common/Util.o Libraries/optiga-trust-x/optiga/comms/ifx_i2c/ifx_i2c.o Libraries/optiga-trust-x/optiga/comms/ifx_i2c/ifx_i2c_config.o Libraries/optiga-trust-x/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.o Libraries/optiga-trust-x/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.o 
	-$(RM) Libraries/optiga-trust-x/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.o Libraries/optiga-trust-x/optiga/comms/optiga_comms.o Libraries/optiga-trust-x/optiga/crypt/optiga_crypt.o Libraries/optiga-trust-x/optiga/dtls/AlertProtocol.o Libraries/optiga-trust-x/optiga/dtls/DtlsFlightHandler.o Libraries/optiga-trust-x/optiga/dtls/DtlsHandshakeProtocol.o Libraries/optiga-trust-x/optiga/dtls/DtlsRecordLayer.o Libraries/optiga-trust-x/optiga/dtls/DtlsTransportLayer.o Libraries/optiga-trust-x/optiga/dtls/DtlsWindowing.o Libraries/optiga-trust-x/optiga/dtls/HardwareCrypto.o Libraries/optiga-trust-x/optiga/dtls/MessageLayer.o Libraries/optiga-trust-x/optiga/dtls/OCP.o Libraries/optiga-trust-x/optiga/dtls/OCPConfig.o Libraries/optiga-trust-x/optiga/util/optiga_util.o Libraries/optiga-trust-x/pal/xmc_dave/pal_gpio.o Libraries/optiga-trust-x/pal/xmc_dave/pal_i2c.o Libraries/optiga-trust-x/pal/xmc_dave/pal_ifx_i2c_config.o Libraries/optiga-trust-x/pal/xmc_dave/pal_os_event.o Libraries/optiga-trust-x/pal/xmc_dave/pal_os_lock.o Libraries/optiga-trust-x/pal/xmc_dave/pal_os_timer.o Libraries/optiga-trust-x/pal/xmc_dave/pal_socket.o Startup/startup_XMC1100.o Startup/system_XMC1100.o main.o src/cmd_process/cmd_iface.o src/serial_io/serial_io_iface.o  xmc2go-TrustX.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
