ARDMK_DIR        := $(HOME)/lib/Arduino-Makefile
ARDUINO_DIR      := $(HOME)/lib/arduino
USER_LIB_PATH    := ./lib

ARDUINO_LIBS     := Adafruit_BME280_Library Adafruit_Sensor Wire SPI EEPROM

BOARD_TAG    = nano
BOARD_SUB   = atmega328
MONITOR_PORT = /dev/ttyUSB0
MONITOR_BAUDRATE  = 9600

CFLAGS_STD        = -std=gnu11
CXXFLAGS_STD      = -std=gnu++1y
CXXFLAGS         += -pedantic -Wall -Wextra

include $(HOME)/lib/Arduino-Makefile/Arduino.mk
