#include <Arduino.h>
#include <Wire.h>
#include <comm.h>

# ifndef IMU_INIT
    # define IMU_INIT
    # include "HardwareSerial.h"
    # include <Adafruit_MPU6050.h>
    # include <Adafruit_Sensor.h>
# endif

int iter = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1,RXp2,TXp2);
}

void loop() {
  Serial.println("Message recieved: ");
  while (Serial2.available()>0){
    char string = Serial2.read();
    Serial.print(string);
  }
  delay(200);
}