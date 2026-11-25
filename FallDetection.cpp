/*
 * FallDetection.cpp
 * Motion calculations and fall decision logic
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#include <Arduino.h>
#include <math.h>
#include "FallDetection.h"
#include "Config.h"

Motion computeMotion(const AccelData &raw) {
  Motion m;
  m.x = raw.x / ACCEL_LSB_PER_G;
  m.y = raw.y / ACCEL_LSB_PER_G;
  m.z = raw.z / ACCEL_LSB_PER_G;

  m.acceleration = sqrt(m.x * m.x + m.y * m.y + m.z * m.z);
  m.angle = atan2(sqrt(m.x * m.x + m.y * m.y), m.z) * 180.0 / PI;
  return m;
}

bool isFall(const Motion &m) {
  return m.angle >= MIN_ANGLE &&
         m.angle <= MAX_ANGLE &&
         m.acceleration > FALL_THRESHOLD;
}
