/*
 * Buzzer.cpp
 * Buzzer setup and fall alarm pattern
 *
 * Project : Fall Detection Device (ESP32 + MPU6050 + Buzzer)
 * Author  : Aashar Pamidiparti
 * Date    : May 2025
 *
 * This code is free to use. You may use, copy, modify, and distribute it
 * freely for any purpose, with or without attribution.
 */

#include <Arduino.h>
#include "Buzzer.h"
#include "Config.h"

void buzzerBegin() {
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  Serial.println("Step 3: Buzzer PWM configured");
}

void triggerFallAlarm() {
  Serial.println("FALL DETECTED!");

  for (int i = 0; i < 5; i++) {
    Serial.print("Beep "); Serial.println(i + 1);
    ledcWrite(BUZZER_CHANNEL, 127);  // 50% duty cycle
    delay(200);

    ledcWrite(BUZZER_CHANNEL, 0);
    delay(100);
  }
  Serial.println("Alarm complete");
}
