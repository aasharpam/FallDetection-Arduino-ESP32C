/*
 * FallDetection.h
 * Motion calculations and fall decision logic
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#ifndef FALL_DETECTION_H
#define FALL_DETECTION_H

#include "Sensor.h"

struct Motion {
  float x;             // Acceleration per axis (g)
  float y;
  float z;
  float acceleration;  // Total acceleration (g)
  float angle;         // Tilt angle (degrees)
};

Motion computeMotion(const AccelData &raw);  // Raw counts -> g, total accel, tilt
bool   isFall(const Motion &m);              // Apply angle + acceleration thresholds

#endif
