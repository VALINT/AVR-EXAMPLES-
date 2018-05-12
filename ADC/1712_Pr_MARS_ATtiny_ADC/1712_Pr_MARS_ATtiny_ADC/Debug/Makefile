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

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../1712_Pr_MARS_ATtiny_ADC.c \
../Measuring.c \
../Reseive164.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
1712_Pr_MARS_ATtiny_ADC.o \
Measuring.o \
Reseive164.o


OBJS_AS_ARGS +=  \
1712_Pr_MARS_ATtiny_ADC.o \
Measuring.o \
Reseive164.o


C_DEPS +=  \
1712_Pr_MARS_ATtiny_ADC.d \
Measuring.d \
Reseive164.d


C_DEPS_AS_ARGS +=  \
1712_Pr_MARS_ATtiny_ADC.d \
Measuring.d \
Reseive164.d


OUTPUT_FILE_PATH +=1712_Pr_MARS_ATtiny_ADC.elf

OUTPUT_FILE_PATH_AS_ARGS +=1712_Pr_MARS_ATtiny_ADC.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler







./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=attiny2313   -o"$@" "$<" 
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

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="1712_Pr_MARS_ATtiny_ADC.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=attiny2313  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "1712_Pr_MARS_ATtiny_ADC.elf" "1712_Pr_MARS_ATtiny_ADC.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "1712_Pr_MARS_ATtiny_ADC.elf" "1712_Pr_MARS_ATtiny_ADC.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "1712_Pr_MARS_ATtiny_ADC.elf" > "1712_Pr_MARS_ATtiny_ADC.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "1712_Pr_MARS_ATtiny_ADC.elf" "1712_Pr_MARS_ATtiny_ADC.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "1712_Pr_MARS_ATtiny_ADC.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "1712_Pr_MARS_ATtiny_ADC.elf" "1712_Pr_MARS_ATtiny_ADC.a" "1712_Pr_MARS_ATtiny_ADC.hex" "1712_Pr_MARS_ATtiny_ADC.lss" "1712_Pr_MARS_ATtiny_ADC.eep" "1712_Pr_MARS_ATtiny_ADC.map" "1712_Pr_MARS_ATtiny_ADC.srec"
	