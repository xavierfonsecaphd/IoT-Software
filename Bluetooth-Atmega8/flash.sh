#!/bin/bash

# avrdude -c usbasp -p atmega8 -P usb -v

executable=programa_exemplo

avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega8 \
	 				-DF_CPU=16000000L -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -L ./uart \
					-I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/libraries/SoftwareSerial \
					-I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard $executable.cpp -o $executable.cpp.o 
		

avr-gcc -w -Os -Wl,--gc-sections -mmcu=atmega8 -o $executable.cpp.elf $executable.cpp.o ./dependencies/uart/uart.o -lm

avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 \
					$executable.cpp.elf $executable.cpp.eep

avr-objcopy -O ihex -R .eeprom $executable.cpp.elf $executable.cpp.hex 


avrdude -c usbasp -p atmega8 -P usb -e

avrdude -C ./dependencies/avrdude.conf -v -p m8 -c usbasp -P usb -b 115200 -D -Uflash:w:$executable.cpp.hex:i -v

# Remove all the temporary files
rm $executable.cpp.d
rm $executable.cpp.eep
rm $executable.cpp.elf
rm $executable.cpp.o
rm $executable.cpp.hex
