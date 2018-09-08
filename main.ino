#include "sensors.hpp"
#include "pm25.h"

/**
 * \file main.ino
 * \brief  Arduino weather station main source file
 */

void setup()
{
    Serial.begin(9600);
    sensors_init();
}

void loop() {
    float f;

    Serial.print("PM2.5 Voltage: ");
    f = PM25_vo();
    Serial.print(f);
    Serial.print("\n\r");
    
    Serial.print("BME280 Temperature: ");
    f = bme280.readTemperature();
    Serial.print(f);
    Serial.print("\n\r");
    
    Serial.print("BME280 Pressure: ");
    f = bme280.readPressure();
    Serial.print(f);
    Serial.print("\n\r");
    
    Serial.print("BME280 Humidity: ");
    f = bme280.readHumidity();
    Serial.print(f);
    Serial.print("\n\r");
    
    Serial.print("\n\r");
    delay(1000);
}
