# Fall Detector

A fall detection device built on an **ESP32** with an **MPU6050** accelerometer and a **buzzer**. When a sudden impact is detected together with a tilted body orientation, the device sounds an alarm.

- **Author:** Aashar Pamidiparti
- **Date:** May 2025
- **License:** Free to use. You may use, copy, modify, and distribute this code freely for any purpose, with or without attribution.

## How it works

Every second the device:

1. Reads raw accelerometer values from the MPU6050.
2. Checks the sensor is healthy (not frozen at zero or saturated). If it is faulty, the sensor is re-initialized.
3. Converts the readings to g-force, then calculates total acceleration and tilt angle.
4. Triggers the alarm if **both** conditions are true:
   - Tilt angle is between `MIN_ANGLE` (30°) and `MAX_ANGLE` (150°)
   - Total acceleration is greater than `FALL_THRESHOLD` (1.4 g)

The alarm is five beeps (200 ms on, 100 ms off) on the buzzer.

## Hardware

| Component | Connection |
|---|---|
| MPU6050 VCC | 3.3V |
| MPU6050 GND | GND |
| MPU6050 SDA | GPIO 21 |
| MPU6050 SCL | GPIO 22 |
| Buzzer (+) | GPIO 23 |
| Buzzer (-) | GND |

## Bill of Materials (BOM)

> **Note:** Get the BOM file (list of components needed to build this project) from [https://www.aasharpam.com/project-fall-detection.html] (https://www.aasharpam.com/project-fall-detection.html).

## Project structure

```
FallDetector/
├── FallDetector.ino     Main sketch: setup() and loop()
├── Config.h             Pins, thresholds and timing constants
├── Sensor.h / .cpp      MPU6050 init, read, fault checks, reset
├── FallDetection.h / .cpp   Motion calculations and fall decision
└── Buzzer.h / .cpp      Buzzer PWM setup and alarm pattern
```

## Getting started

1. Install the **Arduino IDE** and add ESP32 board support.
2. Install the **MPU6050** library (the one that provides `MPU6050.h`, e.g. *MPU6050* by Electronic Cats or the I2Cdevlib version) through the Library Manager.
3. Keep all files together in a folder named `FallDetector`, then open `FallDetector.ino`.
4. Select your ESP32 board and port, then upload.
5. Open the Serial Monitor at **9600 baud** to see diagnostic output.

> **Note:** The buzzer code uses `ledcSetup()` and `ledcAttachPin()`, which work with **ESP32 Arduino core 2.x**. On core 3.x these were replaced by `ledcAttach()`, so `Buzzer.cpp` needs a small update.

## Configuration

All tunable values live in `Config.h`:

| Setting | Default | Meaning |
|---|---|---|
| `FALL_THRESHOLD` | 1.4 | Total acceleration (g) that counts as an impact |
| `MIN_ANGLE` / `MAX_ANGLE` | 30 / 150 | Tilt range (degrees) that counts as a fall |
| `BUZZER_PIN` | 23 | GPIO connected to the buzzer |
| `BUZZER_FREQ` | 1000 | Buzzer tone in Hz |
| `LOOP_DELAY_MS` | 1000 | Time between readings |

## Troubleshooting

- **"MPU6050 connection failed"**: check the wiring above, especially SDA and SCL, and make sure the sensor is powered from 3.3V.
- **"Sensor frozen" or "maxed out" messages**: the code resets the sensor automatically. If it keeps happening, check for loose wires or power issues.
- **No alarm during a test**: lower `FALL_THRESHOLD` in `Config.h` and watch the serial output to see the actual values.
