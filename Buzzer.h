/*
 * Buzzer.h
 * Buzzer setup and fall alarm pattern
 *
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#ifndef BUZZER_H
#define BUZZER_H

void buzzerBegin();      // Configure PWM channel and attach buzzer pin
void triggerFallAlarm(); // Play the 5-beep alarm pattern

#endif
