MCU=atmega644p
F_CPU=8000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
TARGET=open
PROGRAMMER=usbasp # Change this to your programmer type

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).elf: $(TARGET).o
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c -o $@ $<

flash: $(TARGET).hex
	sudo avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(TARGET).o

.PHONY: all clean flash
