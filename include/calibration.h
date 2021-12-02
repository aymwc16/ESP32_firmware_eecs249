#ifndef CALIBRATION_H
#define CALIBRATION_H


#include <ESP32Servo.h>
#include <Arduino.h>
#include <iostream>
#include "haptic_feedback.h"
#include "force_sensor.h"

#define RESISTIVE_FORCE_THRESHOLD 4
#define DANGER_FORCE_THRESHOLD 8

Servo servo1, servo2, servo3, servo4, servo5;
int force1, force2, force3, force4, force5;

long int pinky_min, pinky_max, pinky_rest;
int angle_range;

int noisy_force;


using namespace std;


void calibration(){
    delay(500);
    Serial.println("Gently clench...");
    float force = resistanceToForce(RESISTANCE,analogRead(FF1));
    while (force<=RESISTIVE_FORCE_THRESHOLD){
        servo1.write(MIN_PULSE_WIDTH);
        force = resistanceToForce(RESISTANCE,analogRead(FF1));
        Serial.println(force);
        Serial.println(servo1.read());
    }
    angle_range = 0;
    while (force<=RESISTIVE_FORCE_THRESHOLD){
        servo1.write(-MIN_PULSE_WIDTH);
        angle_range += abs(servo1.read());
        force = resistanceToForce(RESISTANCE,analogRead(FF1));
    }
}

int delta_force(int measurement, int resting_force){
    return(measurement-resting_force);
}


bool confirmation(bool calibrated){
    label1:
    delay(200);
    Serial.println("Please attach the glove to your hand. Are you done? (y/n)");
    while (Serial.available()==0){}
    delay(200);
    if (Serial.read()!='y'){
        Serial.println("Take the time you need! Are your done? (y/n)");
        goto label1;
    }
    else {
        if (!calibrated) {
            Serial.println("Initiating calibration...");
            calibrated = true;
            return(calibrated);
        }
        else {
            bool hesitation = true;
            while (hesitation) {
                delay(200);
                Serial.println("Calibration stored in memory. Would you like to recalibrate? (y/n)");
                while (Serial.available()==0){}
                delay(200);
                if (Serial.read()!='y'){
                    Serial.println("Skipping calibration...");
                    return(calibrated);
                }
                else{
                    Serial.println("Initiating calibration...");
                    return(calibrated);
                }
            }
        }
    }
    calibrated = false;
    Serial.println("An error occured in the confirmation function...");
    return(calibrated);
}


#endif