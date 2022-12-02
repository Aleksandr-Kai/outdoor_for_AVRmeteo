default:
	avrdude -c usbasp -p atmega16 -U flash:w:Debug/Exe/outtemp.hex -B 5
read:
	avrdude -c usbasp -p atmega16 -U flash:r:Debug/Exe/rmeteo.hex -B 5
