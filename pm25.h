#ifndef PM25_H
#define PM25_H

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
 * \brief Convert voltage output to PM2.5 level
 * \param[in] vo the voltage output of the PM2.5 sensor
 * \param[in] vref the voltage of the PM2.5 sensor when it is dust free
 * \param[in] hum
 * \return PM2.5 level in μg/m3
 */
float PM25_vo_to_dust(float vo, float vref, float hum);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
