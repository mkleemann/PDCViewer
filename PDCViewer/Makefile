SHELL := cmd.exe
RM := rm -rf

# set correct MCU
MCU := atmega8
# set frequency of MCU
MCU_SPEED := 4000000UL

USER_OBJS :=

LIBS :=
PROJ :=

O_SRCS :=
C_SRCS :=
S_SRCS :=
S_UPPER_SRCS :=
OBJ_SRCS :=
ASM_SRCS :=
PREPROCESSING_SRCS :=
OBJS :=
OBJS_AS_ARGS :=
C_DEPS :=
C_DEPS_AS_ARGS :=
EXECUTABLES :=
LIB_AS_ARGS :=
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
HEX_FLASH_FILE_PATH :=
HEX_FLASH_FILE_PATH_AS_ARGS :=
HEX_EEPROM_FILE_PATH :=
HEX_EEPROM_FILE_PATH_AS_ARGS :=
LSS_FILE_PATH :=
LSS_FILE_PATH_AS_ARGS :=
MAP_FILE_PATH :=
MAP_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
DOC_EXE := doxygen
DOC_CONF := doxygen.conf

# Every subdirectory with source files must be described here
SUBDIRS :=  \
./can \
./matrixbar \
./spi \
./timer \
./util


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
./can/can_error_mcp2515.c \
./can/can_filter_mcp2515.c \
./can/can_init_mcp2515.c \
./can/can_receive_mcp2515.c \
./can/can_send_mcp2515.c \
./can/can_sleep_mcp2515.c \
./matrixbar/matrixbar.c \
./PDCViewer.c \
./spi/spi.c \
./timer/timer.c


PREPROCESSING_SRCS +=


ASM_SRCS +=


OBJS +=  \
can/can_error_mcp2515.o \
can/can_filter_mcp2515.o \
can/can_init_mcp2515.o \
can/can_receive_mcp2515.o \
can/can_send_mcp2515.o \
can/can_sleep_mcp2515.o \
matrixbar/matrixbar.o \
PDCViewer.o \
spi/spi.o \
timer/timer.o


OBJS_AS_ARGS +=  \
can/can_error_mcp2515.o \
can/can_filter_mcp2515.o \
can/can_init_mcp2515.o \
can/can_receive_mcp2515.o \
can/can_send_mcp2515.o \
can/can_sleep_mcp2515.o \
matrixbar/matrixbar.o \
PDCViewer.o \
spi/spi.o \
timer/timer.o


C_DEPS +=  \
can/can_error_mcp2515.d \
can/can_filter_mcp2515.d \
can/can_init_mcp2515.d \
can/can_receive_mcp2515.d \
can/can_send_mcp2515.d \
can/can_sleep_mcp2515.d \
matrixbar/matrixbar.d \
PDCViewer.d \
spi/spi.d \
timer/timer.d


C_DEPS_AS_ARGS +=  \
can/can_error_mcp2515.d \
can/can_filter_mcp2515.d \
can/can_init_mcp2515.d \
can/can_receive_mcp2515.d \
can/can_send_mcp2515.d \
can/can_sleep_mcp2515.d \
matrixbar/matrixbar.d \
PDCViewer.d \
spi/spi.d \
timer/timer.d

TEMPS += \
can_error_mcp2515.i \
can_filter_mcp2515.i \
can_init_mcp2515.i \
can_receive_mcp2515.i \
can_send_mcp2515.i \
can_sleep_mcp2515.i \
matrixbar.i \
PDCViewer.i \
spi.i \
timer.i

S_SRCS += \
can_error_mcp2515.s \
can_filter_mcp2515.s \
can_init_mcp2515.s \
can_receive_mcp2515.s \
can_send_mcp2515.s \
can_sleep_mcp2515.s \
matrixbar.s \
PDCViewer.s \
spi.s \
timer.s

OUTPUT_FILE_PATH +=PDCViewer.elf

OUTPUT_FILE_PATH_AS_ARGS +=PDCViewer.elf

HEX_FLASH_FILE_PATH +=PDCViewer.hex

HEX_FLASH_FILE_PATH_AS_ARGS +=PDCViewer.hex

HEX_EEPROM_FILE_PATH +=PDCViewer.eep

HEX_EEPROM_FILE_PATH_AS_ARGS +=PDCViewer.eep

LSS_FILE_PATH +=PDCViewer.lss

LSS_FILE_PATH_AS_ARGS +=PDCViewer.lss

MAP_FILE_PATH =PDCViewer.map

MAP_FILE_PATH_AS_ARGS =PDCViewer.map

LIB_AS_ARGS +=libPDCViewer.a

ADDITIONAL_DEPENDENCIES:= $(HEX_FLASH_FILE_PATH) $(LSS_FILE_PATH) $(HEX_EEPROM_FILE_PATH) size

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR/GNU C Compiler





















can/%.o: ./can/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=$(MCU_SPEED) -DMCP_CLOCK=4000000UL  -Os -ffunction-sections -fpack-struct -fshort-enums -Wall -Werror -pedantic -pedantic-errors -c -std=gnu99  -save-temps -mmcu=$(MCU)   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

matrixbar/%.o: ./matrixbar/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=$(MCU_SPEED) -DMCP_CLOCK=4000000UL  -Os -ffunction-sections -fpack-struct -fshort-enums -Wall -Werror -pedantic -pedantic-errors -c -std=gnu99  -save-temps -mmcu=$(MCU)   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

./%.o: ./%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=$(MCU_SPEED) -DMCP_CLOCK=4000000UL  -Os -ffunction-sections -fpack-struct -fshort-enums -Wall -Werror -pedantic -pedantic-errors -c -std=gnu99  -save-temps -mmcu=$(MCU)   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

spi/%.o: ./spi/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=$(MCU_SPEED) -DMCP_CLOCK=4000000UL  -Os -ffunction-sections -fpack-struct -fshort-enums -Wall -Werror -pedantic -pedantic-errors -c -std=gnu99  -save-temps -mmcu=$(MCU)   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<

timer/%.o: ./timer/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=$(MCU_SPEED) -DMCP_CLOCK=4000000UL  -Os -ffunction-sections -fpack-struct -fshort-enums -Wall -Werror -pedantic -pedantic-errors -c -std=gnu99  -save-temps -mmcu=$(MCU)   -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<



# AVR/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

# AVR/GNU C/C++ Linker
$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C/C++ Linker
	$(QUOTE)$(AVR_APP_PATH)avr-gcc.exe$(QUOTE) -Wl,--gc-sections -mrelax  -mmcu=$(MCU)  -Wl,-Map=$(MAP_FILE_PATH_AS_ARGS) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@



$(HEX_FLASH_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature  $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE)

$(HEX_EEPROM_FILE_PATH): $(OUTPUT_FILE_PATH)
	-$(QUOTE)$(AVR_APP_PATH)avr-objcopy.exe$(QUOTE) -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex $(QUOTE)$<$(QUOTE) $(QUOTE)$@$(QUOTE) || exit 0

$(LSS_FILE_PATH): $(OUTPUT_FILE_PATH)
	$(QUOTE)$(AVR_APP_PATH)avr-objdump.exe$(QUOTE) -h -S $(QUOTE)$<$(QUOTE) > $(QUOTE)$@$(QUOTE)

size: $(OUTPUT_FILE_PATH)
	@$(QUOTE)$(AVR_APP_PATH)avr-size.exe$(QUOTE) -C --mcu=$(MCU) $(OUTPUT_FILE_PATH_AS_ARGS)

# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) $(LIB_AS_ARGS) $(HEX_FLASH_FILE_PATH_AS_ARGS) $(HEX_EEPROM_FILE_PATH_AS_ARGS) $(LSS_FILE_PATH_AS_ARGS) $(MAP_FILE_PATH_AS_ARGS) $(OUTPUT_FILE_PATH_AS_ARGS) $(TEMPS) $(S_SRCS)

docu:
	$(DOC_EXE) $(DOC_CONF)

