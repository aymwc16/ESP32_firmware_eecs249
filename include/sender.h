/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Aymeric Wang
 */

#ifndef SENDER_H
#define SENDER_H

#include <Arduino.h>
#include <Wire.h>

/* * * * * * * * * * * * * * * * * * *
* Recommended settings of void setup()
*  
* void setup() {
*   Serial.begin(115200);
* }
* 
* * * * * * * * * * * * * * * * * * * */

void sending() {
  Serial.print("Are you listening?");
  delay(200);
}

#endif