# ifndef __IMU_H__
# define __IMU_H__

# ifndef __IMU_INIT__
    # define __IMU_INIT__
    # include "HardwareSerial.h"
    # include <Adafruit_MPU6050.h>
    # include <Adafruit_Sensor.h>
# endif

Adafruit_MPU6050 mpu;


void Accel(HardwareSerial Serial) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print("Accel ");
    Serial.print("X: ");
    Serial.print(a.acceleration.x, 5);
    Serial.print(" m/s^2, ");
    Serial.print("\tAccel ");
    Serial.print("Y: ");
    Serial.print(a.acceleration.y, 5);
    Serial.print(" m/s^2, ");
    Serial.print("\tAccel ");
    Serial.print("Z: ");
    Serial.print(a.acceleration.z, 5);
    Serial.print(" m/s^2\n");
}

void Gyro(HardwareSerial Serial) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print("Gyro ");
    Serial.print("X: ");
    Serial.print(g.gyro.x, 5);
    Serial.print(" rps, ");
    Serial.print("\tGyro ");
    Serial.print("Y: ");
    Serial.print(g.gyro.y, 5);
    Serial.print(" rps, ");
    Serial.print("\tGyro ");
    Serial.print("Z: ");
    Serial.print(g.gyro.z, 5);
    Serial.print(" rps\n");
}

# endif