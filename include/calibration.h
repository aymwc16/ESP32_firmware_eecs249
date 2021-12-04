/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Aymeric Wang
 */

#ifndef CALIBRATION_H
#define CALIBRATION_H


#include <ESP32Servo.h>
#include <Arduino.h>
#include <iostream>
#include <list>
#include "pin_config.h"
#include "adc_to_newtons.h"

#define RESISTIVE_FORCE_THRESHOLD 4
#define DANGER_FORCE_THRESHOLD 8

/* * * * * * * * * * * * * * * * * * * * * *
 * We define a series of global variables
 * identified from 1 to 5. They each
 * correspond to a servo motor on the
 * glove. In this order:
 *      1. is the little finger
 *      2. is the ring finger
 *      ... and so on ...
 *      5. is the thumb
 * * * * * * * * * * * * * * * * * * * * * */

# define medium (int(MAX_PULSE_WIDTH+MIN_PULSE_WIDTH)/2)

Servo servo1, servo2, servo3, servo4, servo5;
int force1, force2, force3, force4, force5; //ADC force values

//Force values used for calibration
//Long ints avoid a int overflow over the 50-batch sampling
long int rest_force1, rest_force2, rest_force3, rest_force4, rest_force5;
long int clench_force1, clench_force2, clench_force3, clench_force4, clench_force5;

String Fingers[] = {"little", "ring", "middle", "index", "thumb"};
Servo Servos[] = {servo1, servo2, servo3, servo4, servo5};
long int Rest_array[] = {rest_force1,rest_force2,rest_force3,rest_force4,rest_force4,rest_force5};
long int Clench_array[] = {clench_force1,clench_force2,clench_force3,clench_force4,clench_force4,clench_force5};
int FFPins[] = {FF1,FF2,FF3,FF4,FF5};
int SPins[] = {S1,S2,S3,S4,S5};


void calibration(){
    Serial.println("Loose your hand...");
    delay(1500);

    for (int i=0;i<50;i++){
        for(unsigned int a = 0; a<5; a++){
            Servos[a].write(medium);
            delay(2);
            int force = analogRead(FFPins[a]);
            Rest_array[a] += force;
            Serial.println(String("ADC of ")+String(Fingers[a])+String(":\t")+String(force));
        }
        delay(100);
    }
    for(unsigned int a = 0; a<5; a++){
        long int rest = int(Rest_array[a]/50);
        Rest_array[a] = rest;
    }
    
    Serial.println("GENTLY clench...");
    delay(3000);

    for (int i=0;i<50;i++){
        for(unsigned int a = 0; a<5; a++){
            Servos[a].write(medium);
            delay(2);
            int force = analogRead(FFPins[a]);
            Clench_array[a] += force;
            Serial.println(String("ADC of ")+String(Fingers[a])+String(":\t")+String(force));
        }
        delay(100);
    }
    for(unsigned int a = 0; a<5; a++){
        long int clench = Clench_array[a];
        Clench_array[a] = int(clench/50);
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