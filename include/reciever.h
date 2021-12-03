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


int force_message_reciever(){
    char force_message[10];
    char character;
    char msg_delimiter_init[] = "<";
    char msg_delimiter_end[] = ">";
    int i = 0;
    int sPos5 = 0;
    while (!Serial2.available()){}
    while (Serial2.available()>0 && i<10){
        character = Serial2.read();
        if (character == msg_delimiter_init[0]){
            i = 0;
        }
        else if (character == msg_delimiter_end[0]){
            i = 0;
            break;
        }
        else{
            force_message[i] = character;
            i++;
        }
    }
    sPos5 = atoi(force_message);
    Serial.println(String("Force recieved:\t")+String(sPos5));
    return(sPos5);
}

#endif