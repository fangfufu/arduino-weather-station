BOARD_TAG    = nano328
MONITOR_PORT = /dev/ttyUSB0
MONITOR_BAUDRATE  = 9600
CFLAGS_STD        = -std=gnu11
CXXFLAGS_STD      = -std=gnu++11
CXXFLAGS         += -pedantic -Wall -Wextra

include /usr/share/arduino/Arduino.mk
