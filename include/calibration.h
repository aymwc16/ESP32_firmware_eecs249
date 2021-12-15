/**
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
#include "constants.h"

//----------Pins---------------
int FFPins[] = {FF1,FF2,FF3,FF4,FF5};
int SPins[] = {S1,S2,S3,S4,S5};
//-----------Incrementer-----------
//int calibrationTracker = 0;

//---------Tuners ------------
int minimumRange = 50;
float scalerTuner = 200;

//---Force range measurements---
int forceRange[numOfFingers];
float forceScaler[numOfFingers];


//-----Function prototypes-----
void setupServos();
void driveServos();

// To use if you do not want calibration
void reference_forces_list_generator(){
    if (PLATFORM==2){
        restForce[0] = long(2200);
        restForce[1] = long(1200);
        restForce[2] = long(1700);
        restForce[3] = long(2200);
        restForce[4] = long(2500);

        clenchForce[0] = long(2600);
        clenchForce[1] = long(2000);
        clenchForce[2] = long(2400);
        clenchForce[3] = long(2300);
        clenchForce[4] = long(2600);
    }
}

// To use for calibration
void calibration(){

    for(int calibrationTracker = 0; calibrationTracker < numOfFingers; calibrationTracker++){
        Serial.println("Relax your hand...");
        delay(1500);

        for (int i=0; i < samples; i++){
        
            delay(2);
            int force = analogRead(FFPins[calibrationTracker]);
            restForce[calibrationTracker] += force;
            //Serial.println(String("ADC of ")+String(Fingers[calibrationTracker])+String(":\t")+String(force));
            delay(50);
        }
        restForce[calibrationTracker] = restForce[calibrationTracker]/samples;
        Serial.println(restForce[calibrationTracker]);
    
        Servos[calibrationTracker].write(medium);
        Serial.println("GENTLY clench...");
        delay(1000);

        for (int i=0; i < samples; i++){
            
            int force = analogRead(FFPins[calibrationTracker]);
            clenchForce[calibrationTracker] += force;
            //Serial.println(String("ADC of ")+String(Fingers[a])+String(":\t")+String(force));
            delay(50);
        }
        clenchForce[calibrationTracker] = clenchForce[calibrationTracker]/samples;
        Serial.println(clenchForce[calibrationTracker]);
        
        Servos[calibrationTracker].detach();
        setupServos();
        //calibrationTracker++;
    }
}

void calcForceRange(){
    for (int i = 0; i < numOfFingers; i++){
        forceRange[i] = clenchForce[i] - restForce[i];
        if(forceRange[i] < minimumRange){
            Serial.print("Force range is too small on ");
            Serial.println(Fingers[i]);
            if(forceRange[i] < 0) Serial.println("It's less than zero...");
            forceRange[i] = minimumRange;
        }
    }
}

void calcOffsetScaler(){
    for(int i = 0; i < numOfFingers; i++){
        forceScaler[i] = float(forceRange[i]) / scalerTuner;
        Serial.print("Force Scaler for ");
        Serial.print(Fingers[i]);
        Serial.print(" is ");
        Serial.println(forceScaler[i]);
    }
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