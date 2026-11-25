/*
 * FallDetector.ino
 * Main sketch: setup() and loop()
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#include <Wire.h>
#include "Config.h"
#include "Sensor.h"
#include "FallDetection.h"
#include "Buzzer.h"

void setup() {
  Serial.begin(9600);
  Serial.println("=== DIAGNOSTIC MODE ===");
  Serial.println("Step 1: Starting setup...");

  Wire.begin();
  Serial.println("Step 2: I2C initialized");

  buzzerBegin();

  if (!sensorBegin()) {
    Serial.println("ERROR: MPU6050 connection failed!");
    Serial.println("Check your wiring:");
    Serial.println("- VCC to 3.3V");
    Serial.println("- GND to GND");
    Serial.println("- SDA to GPIO 21");
    Serial.println("- SCL to GPIO 22");
    while (1) {
      Serial.println("Stuck in error loop - fix wiring and reset");
      delay(2000);
    }
  }

  Serial.println("=== SETUP COMPLETE ===");
  Serial.println("Starting main loop in 2 seconds...");
  delay(STARTUP_DELAY_MS);
}

void loop() {
  Serial.println("--- Loop iteration ---");

  // Read raw accelerometer data
  AccelData raw;
  Serial.println("Reading accelerometer data...");
  sensorRead(raw);

  Serial.print("Raw values - X: "); Serial.print(raw.x);
  Serial.print(" Y: "); Serial.print(raw.y);
  Serial.print(" Z: "); Serial.println(raw.z);

  // Sensor health checks
  if (sensorIsFrozen(raw)) {
    Serial.println("ERROR: Sensor frozen or readings too low - attempting reset...");
    sensorReset();
    return;
  }
  if (sensorIsMaxedOut(raw)) {
    Serial.println("ERROR: Sensor readings maxed out - attempting reset...");
    sensorReset();
    return;
  }

  // Convert and analyse
  Motion m = computeMotion(raw);

  Serial.print("Normalized - X: "); Serial.print(m.x);
  Serial.print(" Y: "); Serial.print(m.y);
  Serial.print(" Z: "); Serial.println(m.z);

  Serial.print("Acceleration (g): "); Serial.print(m.acceleration);
  Serial.print(" Angle: "); Serial.print(m.angle);
  Serial.println(" degrees");

  // Fall check
  Serial.print("Fall check: Angle ("); Serial.print(m.angle);
  Serial.print(") between "); Serial.print(MIN_ANGLE);
  Serial.print("-"); Serial.print(MAX_ANGLE);
  Serial.print("? and Accel ("); Serial.print(m.acceleration);
  Serial.print(") > "); Serial.print(FALL_THRESHOLD); Serial.print("? ");

  if (isFall(m)) {
    Serial.println("YES - TRIGGERING ALARM!");
    triggerFallAlarm();
  } else {
    Serial.println("No");
  }

  Serial.println("Waiting 1 second...");
  delay(LOOP_DELAY_MS);
}
