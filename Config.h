/*
 * Config.h
 * Pin definitions, thresholds and tuning constants
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ---- Buzzer (PWM) ----
#define BUZZER_PIN         23
#define BUZZER_CHANNEL     0      // PWM channel (0-15)
#define BUZZER_FREQ        1000   // Frequency in Hz
#define BUZZER_RESOLUTION  8      // 8 bit resolution

// ---- Fall detection ----
#define FALL_THRESHOLD     1.4    // Total acceleration (g)
#define MIN_ANGLE          30     // Tilt angle range (degrees)
#define MAX_ANGLE          150

// ---- Sensor scaling and sanity checks ----
#define ACCEL_LSB_PER_G    16384.0   // 1g = 16384 raw for +/-2g range
#define SENSOR_LOW_LIMIT   100       // All axes below this => frozen sensor
#define SENSOR_HIGH_LIMIT  32000     // Any axis above this => maxed out

// ---- Timing (ms) ----
#define STARTUP_DELAY_MS   2000
#define LOOP_DELAY_MS      1000

#endif
