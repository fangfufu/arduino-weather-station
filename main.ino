#include "pm25.h"
#include "Adafruit_BME280.h"

/**
 * \file main.ino
 * \brief  Arduino weather station main source file
 */

Adafruit_BME280 bme280;

void setup()
{
    Serial.begin(9600);
    PM25_init();
    PM25_fan(1);
}

void loop() {
    Serial.print("Voltage: ");
    float vo = PM25_vo();
    Serial.print(vo);
    Serial.print("\n\r");
    delay(1000);
}
