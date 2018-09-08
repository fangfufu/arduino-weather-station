#ifndef PM25_H
#define PM25_H
/**
 * \file pm25.h
 * \brief PM2.5 sensor related functions
 */

/**
 * \brief Initialise the PM2.5 module
 */
void PM25_init();

/**
 * \brief Get the output voltage of the PM2.5 sensor
 */
float PM25_get_vo();

/**
 * \brief Turn the fan of the PM2.5 sensor on/off
 */
void PM25_set_fan_state(int s);

/**
 * \brief Get the fan state of the PM2.5 sensor
 */
int PM25_get_fan_state();

#endif
