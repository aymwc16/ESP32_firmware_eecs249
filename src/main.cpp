/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Adam Curtis, Aymeric Wang
 */

#include <ESP32Servo.h>
#include <Arduino.h>
#include "calibration.h"
#include "pin_config.h"
#include "adc_to_newtons.h"
#include "sender.h"
#include "reciever.h"

bool calibrated = false;
int j = 1500;

void setup() {
	Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1,RXp2,TXp2);
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  for (int a = 0; a<5; a++){
    Servos[a].setPeriodHertz(50);
    Servos[a].attach(SPins[a], MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  }

  /***** DO NOT REMOVE THIS *****
  calibrated = confirmation(calibrated);
  if (calibrated){
    calibration();
  }
  */
  
  Serial.println("Glove ready to work!");
  delay(200);
}



void loop() {
  int may_the_force_bwu;

  force_send(1600);
  may_the_force_bwu = force_message_reciever();
  Serial.println();
  delay(100);
}