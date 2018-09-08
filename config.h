#ifndef CONFIG_H
#define CONFIG_H

/* --------------------------- PM2.5 sensor related ------------------------- */
/** The fan's control pin */
#define PM25_FAN_PIN    2
/** The IR LED control pin */
#define PM25_LED_PIN    9
/** The VO measuring pin */
#define PM25_VO_PIN     A6

/* ------------------------- Calibration related ---------------------------- */
#define CALIBRATION_DATA_ADDR 0

/* -------- The number of sample taken before computing the average --------- */
#define SAMPLE_COUNT 50

#endif
