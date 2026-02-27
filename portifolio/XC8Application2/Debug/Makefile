################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

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
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include/ \
../src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/gpio.c \
../src/main.c \
../src/usart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/gpio.o \
src/main.o \
src/usart.o

OBJS_AS_ARGS +=  \
src/gpio.o \
src/main.o \
src/usart.o

C_DEPS +=  \
src/gpio.d \
src/main.d \
src/usart.d

C_DEPS_AS_ARGS +=  \
src/gpio.d \
src/main.d \
src/usart.d

OUTPUT_FILE_PATH +=aula1_estruturacao.elf

OUTPUT_FILE_PATH_AS_ARGS +=aula1_estruturacao.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
src/gpio.o: ../src/gpio.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.36
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.36\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328__ -DDEBUG  -I"../include"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/main.o: ../src/main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.36
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.36\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328__ -DDEBUG  -I"../include"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/usart.o: ../src/usart.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.36
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.36\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega328  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega328__ -DDEBUG  -I"../include"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.36
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.36\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATmega328  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.7.374\xc8"  -Wl,-Map="aula1_estruturacao.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"C:\Program Files\Microchip\xc8\v2.36\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "aula1_estruturacao.elf" "aula1_estruturacao.hex"
	"C:\Program Files\Microchip\xc8\v2.36\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "aula1_estruturacao.elf" "aula1_estruturacao.eep" || exit 0
	"C:\Program Files\Microchip\xc8\v2.36\bin\avr-objdump.exe" -h -S "aula1_estruturacao.elf" > "aula1_estruturacao.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "aula1_estruturacao.elf" "aula1_estruturacao.hex" "aula1_estruturacao.eep" "aula1_estruturacao.map" "aula1_estruturacao.usersignatures" "aula1_estruturacao.a"  "aula1_estruturacao.lss"
	