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

#define MAX_TRANSM_DELAY 1000

int force_message_reciever(){
    char force_message[10];
    char character;
    char msg_delimiter_init[] = "<";
    char msg_delimiter_end[] = ">";
    int i = 0;
    int robotForce = 0;
    
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
    robotForce = atoi(force_message);
    return(robotForce);
}

int scaleFactor(void){
    int scale = 10;
    int adc_force = force_message_reciever();
    return (adc_force / scale);
}

#endif