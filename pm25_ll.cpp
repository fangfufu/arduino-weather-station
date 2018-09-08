/**
 * \file pm25_ll.c
 * \brief pm25 sensor low level functions
 */

#include "config.h"
#include "pm25_ll.hpp"
#include <Arduino.h>

/** The time the LED should be turned on for before measurement */
#define LED_PREHEAT_TIME 280
/** The time the LED should be kept on for measurement */
#define LED_MEASURE_TIME 40
/** The LED should be off for at least this long before measurement */
#define LED_GUARD_TIME 9680

/** \brief The status of the fan */
static int g_fanState = 0;

/** \brief The status of the IR LED */
static int g_ledState = 0;

/**
 * \note The IR LED is active low.
 */
static void PM25_set_LED_state(int s)
{
    if (s) {
        digitalWrite(PM25_LED_PIN, LOW);
        g_ledState = 1;
    } else {
        digitalWrite(PM25_LED_PIN, HIGH);
        g_ledState = 0;
    }
}

void PM25_set_fan_state(int s)
{
    if (s) {
        digitalWrite(PM25_FAN_PIN, HIGH);
        g_fanState = 1;
    } else {
        digitalWrite(PM25_FAN_PIN, LOW);
        g_fanState = 0;
    }
}

void PM25_init()
{
    pinMode(PM25_FAN_PIN, OUTPUT);
    pinMode(PM25_LED_PIN, OUTPUT);
    PM25_set_LED_state(0);
    PM25_set_fan_state(0);
}

/**
 * \note We make sure the IR LED is off for PM25_LED_GUARD ms, before turning
 * it back on. This is to comply with the specs sheet.
 */
float PM25_get_vo()
{
    PM25_set_LED_state(0);
    delayMicroseconds(LED_GUARD_TIME);
    PM25_set_LED_state(1);
    delayMicroseconds(LED_PREHEAT_TIME);
    float vo = analogRead(PM25_VO_PIN) * ((float)5 / 1024);
    delayMicroseconds(LED_MEASURE_TIME);
    PM25_set_LED_state(0);
    return vo;
}

