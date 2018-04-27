###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = ATmega328P
COMPILER = "WinAVR"
TARGET = Release
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS=-Wall -gdwarf-2 -fsigned-char -MD -MP -DF_CPU=1000000 -Os -mmcu=atmega328p
LDFLAGS=-mmcu=atmega328p

## Processing Tools
CC=avr-gcc.exe
ASM=avr-gcc.exe
LD=avr-gcc.exe
#  E:/5735512083/242-309 Microcontroller and Interfacing/Microcontroller/ATMEGA328P/Release/Release.hex: TOOL=LD
#  Post: $(OBJ) avr-objcopy -O ihex -R .eeprom "./Release.elf" "./Release.hex"
#  Post: $(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Release.elf" "./Release.eep" || exit 0 
#     E:/5735512083/242-309 Microcontroller and Interfacing/Microcontroller/ATMEGA328P/Release/main.o: TOOL=CC
#        E:/5735512083/242-309 Microcontroller and Interfacing/Microcontroller/ATMEGA328P/main.c

# Build tree:
all:	Release

Release:	Release.hex
	cp "Release.hex" "../../ATMEGA328P.hex"

Release.hex:	main.o 
	$(LD) $(LDFLAGS)  -o "./Release.elf" "main.o"
	$(OBJ) avr-objcopy -O ihex -R .eeprom "./Release.elf" "./Release.hex"
	$(OBJ) avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "./Release.elf" "./Release.eep" || exit 0 

main.o:	../main.c 
	$(CC) $(CCFLAGS)  -o "main.o" -c "../main.c"

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf ./main.d

# cleanup - delete all generated files
clean:	tidy
	rm -rf Release.hex
	rm -rf main.o

