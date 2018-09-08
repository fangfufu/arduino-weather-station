/**
 * \file pm25_ll.c
 * \brief pm25 sensor low level functions
 */

#include <elapsedMillis.h>
#include <Arduino.h>
#include "pm25.h"

/** The time the LED should be turned on for before measurement */
#define LED_PREHEAT_TIME 280
/** The time the LED should be kept on for measurement */
#define LED_MEASURE_TIME 40
/** The LED should be off for at least this long before measurement */
#define LED_GUARD_TIME 9680

/** \brief The reference output voltage */
static int g_fanState = 0;

/** \brief The status of the fan */
static int g_vref = -1;

/** \brief The status of the IR LED */
static int g_ledState = 0;

/** \brief How long the fan had been stopped */
elapsedMillis g_fanStopped;

/**
 * \note The IR LED is active low.
 */
static void PM25_LED(int s)
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
        g_fanStopped = 0;
    }
}

int PM25_get_fan_state()
{
    return g_fanState;
}

unsigned long PM25_get_fan_stop_time_elapsed
{
    if(!PM25_get_fan_state()) {
        return g_fanStopped;
    } else {
        return 0;
    }
}

void PM25_init()
{
    pinMode(PM25_FAN_PIN, OUTPUT);
    pinMode(PM25_LED_PIN, OUTPUT);
    PM25_LED(0);
    PM25_fan(0);
}

/**
 * \note We make sure the IR LED is off for PM25_LED_GUARD ms, before turning
 * it back on. This is to comply with the specs sheet.
 */
float PM25_get_vo()
{
    PM25_LED(0);
    delayMicroseconds(LED_GUARD_TIME);
    PM25_LED(1);
    delayMicroseconds(LED_PREHEAT_TIME);
    float vo = analogRead(VO_PIN) * ((float)5 / 1024);
    delayMicroseconds(LED_MEASURE_TIME);
    PM25_LED(0);
    return vo;
}

