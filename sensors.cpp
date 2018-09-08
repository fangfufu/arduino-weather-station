/**
 * \file sensors.h
 */

#include "config.h"
#include "sensors.hpp"
#include "pm25_ll.hpp"
#include "Adafruit_BME280.h"

Adafruit_BME280 bme280;
float pm25_vref;

void sensors_calibrate()
{
    PM25_set_fan_state(0);
    pm25_vref = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        pm25_vref += PM25_get_vo()/SAMPLE_COUNT;
    }
}

void sensors_init()
{
    PM25_init();
    bme280.begin();
    PM25_set_fan_state(0);
    sensors_calibrate();
}

/**
 * \brief Convert voltage output to PM2.5 level
 * \param[in] vo the voltage output of the PM2.5 sensor
 * \param[in] vref the voltage of the PM2.5 sensor when it is dust free
 * \param[in] hum the humidity level in percentage, e.g. 50 for 50%
 * \return PM2.5 level in μg/m3
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
static float PM25_vo_to_aerosol(float vo, float vref, float hum)
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

measure_t sensors_measure()
{
    measure_t m;
    m.temp = 0;
    m.pres = 0;
    m.hum = 0;
    m.vo = 0;
    m.vref = pm25_vref;
    PM25_set_fan_state(1);
    delay(FAN_SPIN_TIME);

    for (int i = 0; i < SAMPLE_COUNT; i++) {
        m.temp += bme280.readTemperature()/SAMPLE_COUNT;
        m.pres += bme280.readPressure()/SAMPLE_COUNT;
        m.hum += bme280.readHumidity()/SAMPLE_COUNT;
        m.vo += PM25_get_vo()/SAMPLE_COUNT;
    }
    m.vo -= PM25_FUDGE;
    m.pm25 = PM25_vo_to_aerosol(m.vo, pm25_vref, m.hum);
    PM25_set_fan_state(0);
    return m;
}




