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
  String formatted_message;
  formatted_message ="<"+message+">";
  Serial2.print(formatted_message);
  Serial.println("I sent message:\t"+String(formatted_message));
  delay(200);
}

void force_send(int ADC_input) {
  String force_string = String(ADC_input);
  message_send(force_string);
}

#endif