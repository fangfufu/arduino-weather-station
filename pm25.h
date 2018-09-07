#ifndef PM25_H
#define PM25_H
/**
 * \file pm25.h
 * \brief PM2.5 sensor related functions
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialise the PM2.5 module
 */
void PM25_init();

/**
 * \brief Get the output voltage of the PM2.5 sensor
 */
float PM25_vo();

/**
 * \brief Turn the fan of the sensor on/off
 */
void PM25_fan(int s);

/**
 * \brief Get the PM2.5 level 
 */
float PM25_dust();

/**
 * \brief Re-calibrate the sensor
 */
float PM25_recalibrate();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
