#include <Arduino.h>
#include <Wire.h>

#include "imu.h"
#ifndef __IMU_INIT__
  #define __IMU_INIT__
  #include "HardwareSerial.h"
  #include <Adafruit_MPU6050.h>
  #include <Adafruit_Sensor.h>
#endif

void setup() {
  Serial.begin(115200);
  // while (!Serial);
  Serial.println("MPU6050 OLED demo");

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");
  delay(500); // Pause for 2 seconds
}

void loop() {
  Accel(Serial);
  delay(100);
}