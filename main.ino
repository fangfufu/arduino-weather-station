#include "pm25.h"

/**
 * \file main.ino
 * \brief  Arduino weather station main source file
 */
/** The fan's control pin */
#define FAN_PIN    2

void setup()
{
    Serial.begin(9600);
    PM25_init();
    PM25_fan(1);
}

void loop() {
    Serial.print("Voltage: ");
    float vo = PM25_measure_vo();
    Serial.print(vo);
    Serial.print("\n\r");
    delay(1000);
}
