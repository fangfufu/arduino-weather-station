#ifndef SETTINGS_H
#define SETTINGS_H
/**
 * \file settings.h
 * \brief EEPROM related functions
 * \details We centrally manage the EEPROM allocation here
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief save PM25 calibration voltage
 */
void settings_save_PM25(float i);

/**
 * @brief load PM25 sensor calibration voltage
 */
float settings_load_PM25();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
