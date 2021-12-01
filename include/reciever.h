/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Aymeric Wang
 */

#ifndef RECIEVER_H
#define RECIEVER_H

#include <Arduino.h>
#include <Wire.h>

/* * * * * * * * * * * * * * * * * * *
* @setup 
* void setup() {
*   Serial.begin(115200);
*   Serial2.begin(115200, SERIAL_8N1,RXp2,TXp2);
* }
* 
* @loop
* void loop() {
*   Serial.println("Message recieved: ");
*   while (Serial2.available()>0){
*       char string = Serial2.read();
*       Serial.print(string);
*   }
*   delay(200);
* }
* * * * * * * * * * * * * * * * * * * */

int iter = 0;

#endif