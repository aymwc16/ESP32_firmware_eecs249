/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Aymeric Wang
 */

#ifndef RECIEVER_H
#define RECIEVER_H

#include <Arduino.h>
#include <Wire.h>
#include <string.h>

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

int force_message_reciever(){
    char force[10];
    char character;
    char alpha;
    int i = 0;
    int sPos5 = 0;
    while (Serial2.available()>0){
        character = Serial2.read();
        int result;
        //Serial.print(string);

        // UNDER CONSTRUCTION !!!
        /*
        if (character == "<"){}
        else if (character[0] == ">"){
            break;
        }
        else{
            force[i] = character[0];
            i++;
        }
        */
    }

    Serial.println(String("Force recieved:\t")+String(sPos5));
    sPos5 = atoi(force);
    return(sPos5);
}

#endif