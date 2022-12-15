###############################################################################
# Makefile for the project first
###############################################################################

## General Flags
PROJECT = first
MCU = atmega128
TARGET = first.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=first.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"E:\msprocesser\first\Source" -I"E:\msprocesser\first\Source\include" -I"E:\msprocesser\first\Source\portable" 

## Objects that must be built in order to link
OBJECTS = fnd.o main.o motor.o switch.o temperature.o buzzer.o utils.o lcd.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) first.hex first.eep first.lss## Compile
fnd.o: ../fnd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

motor.o: ../motor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

switch.o: ../switch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

temperature.o: ../temperature.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

buzzer.o: ../buzzer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

utils.o: ../utils.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd.o: ../lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) first.elf dep/* first.hex first.eep first.lss first.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

