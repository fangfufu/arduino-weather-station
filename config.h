#ifndef CONFIG_H
#define CONFIG_H

/** \brief The fan's control pin */
#define PM25_FAN_PIN    2

/** \brief The IR LED control pin */
#define PM25_LED_PIN    9

/** \brief The VO measuring pin */
#define PM25_VO_PIN     A6

/**
 * \brief PM2.5 fudge factor
 * \details This accounts for the voltage difference due to turning on the
 * fan pin
 */
#define PM25_FUDGE      0.25

/** \brief The number of sample taken before computing the average */
#define SAMPLE_COUNT 50

/**
 * \brief Fan spin time
 * \details The number of milliseconds the fan has to spin before taking
 * measurement
 */
#define FAN_SPIN_TIME 15*1000

#endif
