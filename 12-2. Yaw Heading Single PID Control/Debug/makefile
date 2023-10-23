################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := 12-2. Yaw Heading Single PID Control
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
12-2.\ Yaw\ Heading\ Single\ PID\ Control.elf \

MAP_FILES += \
12-2.\ Yaw\ Heading\ Single\ PID\ Control.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
12-2.\ Yaw\ Heading\ Single\ PID\ Control.list \


# All Target
all: main-build

# Main-build Target
main-build: 12-2.\ Yaw\ Heading\ Single\ PID\ Control.elf secondary-outputs

# Tool invocations
12-2.\ Yaw\ Heading\ Single\ PID\ Control.elf 12-2.\ Yaw\ Heading\ Single\ PID\ Control.map: $(OBJS) $(USER_OBJS) C:\Users\yeosu\STM32CubeIDE\workspace_1.10.1\12-2.\ Yaw\ Heading\ Single\ PID\ Control\STM32F405RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "12-2. Yaw Heading Single PID Control.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\yeosu\STM32CubeIDE\workspace_1.10.1\12-2. Yaw Heading Single PID Control\STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="12-2. Yaw Heading Single PID Control.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

12-2.\ Yaw\ Heading\ Single\ PID\ Control.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "12-2. Yaw Heading Single PID Control.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 12-2.\ Yaw\ Heading\ Single\ PID\ Control.elf 12-2.\ Yaw\ Heading\ Single\ PID\ Control.list 12-2.\ Yaw\ Heading\ Single\ PID\ Control.map 12-2.\\ Yaw\\ Heading\\ Single\\ PID\\ Control.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
