# Compiler and Linker
CXX=g++
CC=avr-gcc
OBJCOPY=avr-objcopy

# MCU details
MCU=atmega644p
F_CPU=8000000UL
CFLAGS_AVR=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Target
TARGET=open

# Programmer
PROGRAMMER=usbasp

# Qt and MySQL paths
QT_INC=/usr/include/qt
QT_LIB=/usr/lib/x86_64-linux-gnu
MYSQL_INC=/usr/include/mysql
MYSQL_LIB=/usr/lib/x86_64-linux-gnu

# Compiler flags
CXXFLAGS=-I$(QT_INC) -I$(MYSQL_INC)
LDFLAGS=-L$(QT_LIB) -L$(MYSQL_LIB) -lQt5Core -lQt5Gui -lQt5Widgets -lmysqlclient

# Rules
all: $(TARGET).elf

$(TARGET).elf: $(TARGET).o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

flash: $(TARGET).hex
	sudo avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(TARGET).o

.PHONY: all clean flash
