################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/RTOS2/CMSIS/RTOS2/Heap/Heap_1/subdir.mk
-include Middlewares/RTOS2/CMSIS/RTOS2/Core/TZ_Secure_Only/subdir.mk
-include Middlewares/LwIP/system/OS/subdir.mk
-include Middlewares/LwIP/src/netif/ppp/polarssl/subdir.mk
-include Middlewares/LwIP/src/netif/ppp/subdir.mk
-include Middlewares/LwIP/src/netif/subdir.mk
-include Middlewares/LwIP/src/core/ipv6/subdir.mk
-include Middlewares/LwIP/src/core/ipv4/subdir.mk
-include Middlewares/LwIP/src/core/subdir.mk
-include Middlewares/LwIP/src/apps/tftp/subdir.mk
-include Middlewares/LwIP/src/apps/sntp/subdir.mk
-include Middlewares/LwIP/src/apps/snmp/subdir.mk
-include Middlewares/LwIP/src/apps/smtp/subdir.mk
-include Middlewares/LwIP/src/apps/netbiosns/subdir.mk
-include Middlewares/LwIP/src/apps/mqtt/subdir.mk
-include Middlewares/LwIP/src/apps/mdns/subdir.mk
-include Middlewares/LwIP/src/apps/lwiperf/subdir.mk
-include Middlewares/LwIP/src/apps/altcp_tls/subdir.mk
-include Middlewares/LwIP/src/api/subdir.mk
-include LWIP/Target/subdir.mk
-include LWIP/App/subdir.mk
-include Drivers/lan8742/subdir.mk
-include Drivers/STM32N6xx_HAL_Driver/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Projet_ETRS923_YY_Appli
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Projet_ETRS923_YY_Appli.elf \

MAP_FILES += \
Projet_ETRS923_YY_Appli.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Projet_ETRS923_YY_Appli.list \

OBJCOPY_BIN += \
Projet_ETRS923_YY_Appli.bin \


# All Target
all: main-build

# Main-build Target
main-build: Projet_ETRS923_YY_Appli.elf secondary-outputs

# Tool invocations
Projet_ETRS923_YY_Appli.elf Projet_ETRS923_YY_Appli.map: $(OBJS) $(USER_OBJS) C:\Workspace\Projet_ETRS923_YY\Appli\STM32N657X0HXQ_LRUN.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Projet_ETRS923_YY_Appli.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m55 -T"C:\Workspace\Projet_ETRS923_YY\Appli\STM32N657X0HXQ_LRUN.ld" --specs=nosys.specs -Wl,-Map="Projet_ETRS923_YY_Appli.map" -Wl,--gc-sections -static -Wl,--cmse-implib -Wl,--out-implib=./secure_nsclib.o -u _printf_float --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Projet_ETRS923_YY_Appli.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Projet_ETRS923_YY_Appli.list"
	@echo 'Finished building: $@'
	@echo ' '

Projet_ETRS923_YY_Appli.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Projet_ETRS923_YY_Appli.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Projet_ETRS923_YY_Appli.bin Projet_ETRS923_YY_Appli.elf Projet_ETRS923_YY_Appli.list Projet_ETRS923_YY_Appli.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
