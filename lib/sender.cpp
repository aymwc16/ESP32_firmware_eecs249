#include <Arduino.h>
#include <Wire.h>

# ifndef IMU_INIT
    # define IMU_INIT
    # include "HardwareSerial.h"
    # include <Adafruit_MPU6050.h>
    # include <Adafruit_Sensor.h>
# endif

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Are you listening?");
  delay(200);
}