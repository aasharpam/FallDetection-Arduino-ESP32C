/*
 * Sensor.cpp
 * MPU6050 access: init, read, fault check, reset
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#include <Wire.h>
#include <MPU6050.h>
#include "Sensor.h"
#include "Config.h"

static MPU6050 mpu;

static void configureRanges() {
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
}

bool sensorBegin() {
  Serial.println("Step 4: Attempting MPU6050 initialization...");
  mpu.initialize();
  Serial.println("Step 5: MPU6050 initialize() completed");

  Serial.println("Step 6: Testing MPU6050 connection...");
  if (!mpu.testConnection()) {
    return false;
  }
  Serial.println("Step 7: MPU6050 connection successful!");

  configureRanges();
  Serial.println("Step 8: Scale ranges set");
  return true;
}

void sensorRead(AccelData &data) {
  mpu.getAcceleration(&data.x, &data.y, &data.z);
}

bool sensorIsFrozen(const AccelData &d) {
  return (d.x == 0 && d.y == 0 && d.z == 0) ||
         (abs(d.x) < SENSOR_LOW_LIMIT &&
          abs(d.y) < SENSOR_LOW_LIMIT &&
          abs(d.z) < SENSOR_LOW_LIMIT);
}

bool sensorIsMaxedOut(const AccelData &d) {
  return abs(d.x) > SENSOR_HIGH_LIMIT ||
         abs(d.y) > SENSOR_HIGH_LIMIT ||
         abs(d.z) > SENSOR_HIGH_LIMIT;
}

void sensorReset() {
  Serial.println("Resetting MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Reset failed - connection test failed");
    delay(1000);
    return;
  }

  configureRanges();
  Serial.println("MPU6050 reset successful");
  delay(500);  // Give it time to stabilize
}
