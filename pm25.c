#include <Arduino.h>

#include "pm25.h"

/** The time the LED should be turned on for before measurement */
#define LED_PREHEAT_TIME 280
/** The time the LED should be kept on for measurement */
#define LED_MEASURE_TIME 40
/** The LED should be off for at least this long before measurement */
#define LED_GUARD_TIME 9680
/** The fan's control pin */
#define FAN_PIN    2
/** The IR LED control pin */
#define LED_PIN    9
/** The VO measuring pin */
#define VO_PIN     A6

/**
 * \note The IR LED is active low.
 */
void PM25_LED(int s)
{
    s ? digitalWrite(LED_PIN, LOW) : digitalWrite(LED_PIN, HIGH);
}

void PM25_init()
{
    pinMode(FAN_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    PM25_LED(0);
    PM25_fan(0);
}

/**
 * \note We make sure the IR LED is off for PM25_LED_GUARD ms, before turning 
 * it back on. This is to comply with the specs sheet.
 */
float PM25_measure_vo()
{

    PM25_LED(1);
    delayMicroseconds(LED_PREHEAT_TIME);
    float vo = analogRead(VO_PIN) * ((float)5 / 1024); 
    delayMicroseconds(LED_MEASURE_TIME);
    PM25_LED(0);
    delayMicroseconds(LED_GUARD_TIME);
    return vo;
}

void PM25_fan(int s)
{
    s ? digitalWrite(FAN_PIN, HIGH) : digitalWrite(FAN_PIN, LOW);
}
