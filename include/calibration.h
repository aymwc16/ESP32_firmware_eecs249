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

long int rest_force1, rest_force2, rest_force3, rest_force4, rest_force5;
long int clench_force1, clench_force2, clench_force3, clench_force4, clench_force5;    
long int flat_force1, flat_force2, flat_force3, flat_force4, flat_force5;

using namespace std;


void calibration(){
    delay(500);
    int medium = int((MIN_PULSE_WIDTH+MAX_PULSE_WIDTH)/2);
    for (int i=0;i<50;i++){
        servo1.write(medium);
        servo2.write(medium);
        servo3.write(medium);
        servo4.write(medium);
        servo5.write(medium);

        rest_force1 += analogRead(FF1);
        rest_force2 += analogRead(FF2);
        rest_force3 += analogRead(FF3);
        rest_force4 += analogRead(FF4);
        rest_force5 += analogRead(FF5);
        Serial.println(rest_force1);
        Serial.println(rest_force2);
        Serial.println(rest_force3);
        Serial.println(rest_force4);
        Serial.println(rest_force5); 
        delay(100);
    }
    rest_force1 = int(rest_force1/50);
    rest_force2 = int(rest_force2/50);
    rest_force3 = int(rest_force3/50);
    rest_force4 = int(rest_force4/50);
    rest_force5 = int(rest_force5/50);
    delay(3000);

    Serial.println("Gently clench...");

    for (int i=0;i<50;i++){
        servo1.write(medium);
        servo2.write(medium);
        servo3.write(medium);
        servo4.write(medium);
        servo5.write(medium);

        clench_force1 += analogRead(FF1);
        clench_force2 += analogRead(FF2);
        clench_force3 += analogRead(FF3);
        clench_force4 += analogRead(FF4);
        clench_force5 += analogRead(FF5);
        delay(100);
    }
    clench_force1 = int(clench_force1/50);
    clench_force2 = int(clench_force2/50);
    clench_force3 = int(clench_force3/50);
    clench_force4 = int(clench_force4/50);
    clench_force5 = int(clench_force5/50);

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