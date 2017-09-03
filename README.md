# arduino-weather-station
The code for running this:
https://www.fangfufu.co.uk/wiki/doku.php?id=public:raspberry_pi_weather_station_board

## Implementation Notes
The address for my BME280 sensor is `0x76` rather than the default `0x77`. You 
need to change it in `Adafruit_BME280.h`.

## Compilation

    sudo apt-get install arduino arduino-mk
    make

## Upload to Arduino

    make upload
    
Note that you might want to change the stuff in the Makefile

## License
    Arduino weather Station
    Copyright (C) 2017  Fufu Fang

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
