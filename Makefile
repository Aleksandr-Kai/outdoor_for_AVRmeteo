default:
	avrdude -c usbasp -p atmega8 -U flash:w:Debug/Exe/outtemp.hex -B 5
read:
	avrdude -c usbasp -p atmega8 -U flash:r:Debug/Exe/rmeteo.hex -B 5
fuse: # not work. usbasp frequency incompatible
	avrdude -c usbasp -p atmega8 -U lfuse:w:0x1E:m	-U hfuse:w:0xBF:m