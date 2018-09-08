#include "sensors.hpp"
#include "pm25_ll.hpp"

/**
 * \file main.ino
 * \brief  Arduino weather station main source file
 */

void setup()
{
    Serial.begin(9600);
    sensors_init();
}

measure_t m;
char buf[128];
char temp_s[10];
char pres_s[10];
char hum_s[10];
char pm25_s[10];
char vo_s[10];
char vref_s[10];

void loop() {
    measure_t m = sensors_measure();

    dtostrf(m.temp, 1, 2, temp_s);
    dtostrf(m.pres, 1, 2, pres_s);
    dtostrf(m.hum, 1, 2, hum_s);
    dtostrf(m.pm25, 1, 2, pm25_s);
    dtostrf(m.vo, 1, 2, vo_s);
    dtostrf(m.vref, 1, 2, vref_s);

    snprintf(buf, sizeof(buf), "%s, %s, %s, %s, %s, %s\r\n",
                   temp_s, pres_s, hum_s, pm25_s, vo_s, vref_s);
    Serial.print(buf);
//     delay(300000);      // 5 minutes
    delay(5000);      // 5 sec
    sensors_calibrate();
//     delay(300000);      // 5 minutes
    delay(5000);      // 5 sec
}
