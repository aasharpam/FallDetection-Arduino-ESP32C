/*
 * Sensor.h
 * MPU6050 access: init, read, fault check, reset
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

struct AccelData {
  int16_t x;
  int16_t y;
  int16_t z;
};

bool sensorBegin();                          // Initialize + verify + configure
void sensorRead(AccelData &data);            // Read raw accelerometer values
bool sensorIsFrozen(const AccelData &data);  // Zeros / suspiciously low values
bool sensorIsMaxedOut(const AccelData &data);// Saturated readings
void sensorReset();                          // Re-initialize after a fault

#endif
