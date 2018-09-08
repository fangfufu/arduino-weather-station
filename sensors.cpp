/**
 * \file sensors.h
 */

#include "config.h"
#include "sensors.hpp"
#include "pm25_ll.hpp"
#include "Adafruit_BME280.h"
#include <EEPROM.h>


struct CalibrationData{
    float pm25_vref;
};

Adafruit_BME280 bme280;
CalibrationData calibration_data;
float pressure;
float humidity;
float temperature;
float pm25_vo;


static void save_calibration_data()
{
    EEPROM.put(CALIBRATION_DATA_ADDR, calibration_data);
}

static void load_calibration_data()
{
    EEPROM.get(CALIBRATION_DATA_ADDR, calibration_data);
}

void sensors_init()
{
    load_calibration_data();
    PM25_init();
    bme280.begin();
    PM25_fan(0);
    sensors_measure();
}

void sensors_measure()
{
    pressure = 0;
    humidity = 0;
    temperature = 0;
    int fan_state = PM25_get_fan_state();
    /* Only update PM2.5 sensor measurement when the fan is spinning */
    if (fan_state) {
        pm25_vo = 0;
    }
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        temperature += bme280.readTemperature()/SAMPLE_COUNT;
        pressure += bme280.readPressure()/SAMPLE_COUNT;
        humidity += bme280.readHumidity()/SAMPLE_COUNT;
        if (fan_state) {
            pm25_vo += PM25_vo()/SAMPLE_COUNT;
        }
    }
}

void sensors_calibrate()
{

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
static float PM25_vo_to_dust(float vo, float vref, float hum)
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
