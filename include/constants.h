#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>
#include <ESP32Servo.h>

// Maximum ADC force threshold to be applied on finger articulations
#define MAXFORCE 3000


// Hardcoded platform parameter value

/* * * * * * * *
 * PLATFORM 1 = Pincher
 * PLATFORM 2 = Glove
 * * * * * * * */

#define PLATFORM 2
#if PLATFORM!=1 & PLATFORM!=2
    #error [ERROR] PLATFORM must be 1 or 2
#endif

// Constants for calibration.h
# define numOfFingers 5
# define medium (int(MAX_PULSE_WIDTH+MIN_PULSE_WIDTH)/2)
# define samples 50

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

int servoPosition[] = {1000, 1000, 1000, 1000, 1000};
int force[numOfFingers];

String Fingers[] = {"little", "ring", "middle", "index", "thumb"};
Servo Servos[numOfFingers];

long int restForce[numOfFingers];
long int clenchForce[numOfFingers];


#endif