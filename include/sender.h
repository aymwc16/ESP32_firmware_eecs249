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


void message_send(String message){
  Serial2.print(message);
  delay(200);
}

void force_send(int ADC_input) {
  String force_string = String(ADC_input);
  message_send(force_string);
}

#endif