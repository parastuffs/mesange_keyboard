1. avr-gcc -Os -DF_CPU=16000000L -mmcu=atmega32u4 -c -o blinky.o blinky.c
2. avr-gcc -mmcu=atmega32u4 blinky.o -o blinky
3. avr-objcopy -O ihex -R .eeprom blinky blinky.hex
4. Short the pins RST and GND to enter bootloader mode.
5. avrdude -F -V -c avr109 -p atmega32u4 -P /dev/ttyACM0 -b 115200 -U flash:w:blinky.hex

## Questions
- How do I know wich input does what?

## Answers
- Embedded LEDs are on PB0 (RX) and PD5 (TX)

## References
- https://create.arduino.cc/projecthub/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
- https://deskthority.net/viewtopic.php?f=7&t=8448&start=
- https://arduino.stackexchange.com/questions/21492/will-a-ino-arduino-sketch-compile-directly-on-gcc-avr
- https://www.instructables.com/AVR-Programming-with-Arduino-AVRdude-and-AVR-gcc/
- https://stackoverflow.com/questions/32413959/avr-gcc-with-arduino