#ifndef CONFIG_H
#define CONFIG_H

/* --------------------------- PM2.5 sensor related ------------------------- */
/** \brief The fan's control pin */
#define PM25_FAN_PIN    2

/** \brief The IR LED control pin */
#define PM25_LED_PIN    9

/** \brief The VO measuring pin */
#define PM25_VO_PIN     A6

/** \brief The number of sample taken before computing the average */
#define SAMPLE_COUNT 50

/**
 * \brief Fan spin time
 * \details The number of milliseconds the fan has to spin before taking
 * measurement
 */
#define FAN_SPIN_TIME 1000

#endif
