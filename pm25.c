#include <Arduino.h>
#include <EEPROM.h>

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

/** The reference output voltage */
int g_fanState = 0;

/** The status of the fan */
int g_vref = -1;

/** The status of the IR LED */
int g_ledState = 0;

/**
 * \brief Convert voltage output to PM2.5 level
 * \param[in] vo the voltage output of the PM2.5 sensor
 * \param[in] vref the voltage of the PM2.5 sensor when it is dust free
 * \param[in] hum
 * \return PM2.5 level in μg/m3
 */
float PM25_vo_to_dust(float vo, float vref, float hum);


/**
 * \note The IR LED is active low.
 */
void PM25_LED(int s)
{
    if (s) {
        digitalWrite(LED_PIN, LOW);
        g_ledState = 1;
    } else {
        digitalWrite(LED_PIN, HIGH);
        g_ledState = 0;
    }
        
}

void PM25_fan(int s)
{
    if (s) {
        digitalWrite(FAN_PIN, HIGH);
        g_fanState = 1;
    } else {
        digitalWrite(FAN_PIN, LOW);
        g_fanState = 0;
    }
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
float PM25_vo()
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

/**
 * \note Copied straight from the datasheet
 * Conversion formula (draft):
 * P M2.5 level (μg/m3) = α × β ×（Vo[mV] – Vs[mV]）
 * Note. Do not temperature correction, an estimates in actual environment.
 * α ： Conversion factor in the true environment
 * Recommendation ： 0.6
 *  （β ： Humidity factor〔h=humidity(%)〕）
 *  〔 β ＝ {1-0.01467(h-50)} (h>50) 〕
 *  〔 β ＝ 1 (h≦50) 〕
 */
float PM25_vo_to_dust(float vo, float vref, float hum)
{
    float a = 0.6;
    float b;
    if (hum > 50) {
        b = 1-0.01467 * (hum -50);
    } else {
        b = 1;
    }
    float pm25 = a * b * (vo - vref);
    return pm25;
}
