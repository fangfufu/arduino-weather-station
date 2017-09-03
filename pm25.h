#ifndef PM25_H
#define PM25_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialise the PM25 module
 */
void PM25_init();

/**
 * \brief Get the output voltage of the PM25 sensor
 */
float PM25_measure_vo();

/**
 * \brief Turn the fan of the sensor on/off
 */
void PM25_fan(int s);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
