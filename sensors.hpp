#ifndef SENSORS_H
#define SENSORS_H

/**
 * \brief measurement data type
 */
struct measure_t {
    float temp;
    float pres;
    float hum;
    float pm25;
    float vo;
    float vref;
};

/**
 * \brief Initialise sensors
 */
void sensors_init();

/**
 * \brief Calibrate the PM2.5 sensor
 */
void sensors_calibrate();

/**
 * \brief Run sensor measurement routine
 */
measure_t sensors_measure();
#endif
