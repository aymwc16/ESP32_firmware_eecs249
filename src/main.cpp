/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Adam Curtis, Aymeric Wang
 */

#include <ESP32Servo.h>
#include <Arduino.h>
#include "calibration.h"
#include "haptic_feedback.h"
#include "comm.h"

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

  servo1.setPeriodHertz(50); 
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  servo4.setPeriodHertz(50);
  servo5.setPeriodHertz(50);

  servo1.attach(S1, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  servo2.attach(S2, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  servo3.attach(S3, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  servo4.attach(S4, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  servo5.attach(S5, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  
  //calibrated = confirmation(calibrated);
  if (calibrated){
    //calibration();
  }
  
  Serial.println("Glove ready to work!");
  delay(200);
}

/*
void loop() {
  //calibrated = confirmation(calibrated);
	delay(200);
}
*/


void loop() {
  /*
  force1 = analogRead(FF1);
  force2 = analogRead(FF2);
  force3 = analogRead(FF3);
  force4 = analogRead(FF4);
  force5 = analogRead(FF5);
  */
  
//	if(force1 > 220){ 
//    j += ((force1 - 200)/20);
//	} else if (force1 < 180) {
//    j -= ((200 - force1)/20);
//	}

//  if(j>2000) j = 2000;
//  if(j<1000) j = 1000;
  //Serial2.println("F1");
	
  //Serial2.print(String(force1));
  
  
  /*
  Serial2.println("F2");
  Serial2.println(force2);
  Serial2.println("F3");
  Serial2.println(force3);
  Serial2.println("F4");
  Serial2.println(force4);
  Serial2.println("F5");
  Serial2.println(force5);
  */
  //Serial.println(j);



  /*
  servo1.write(1500);
  servo2.write(1500);
  servo3.write(1500);
  servo4.write(1500);
  servo5.write(1500);
  */

  char force[10];
  int i = 0;
  delay(50);
  while (!Serial2.available());
  while (Serial2.available()>0){
    char string = Serial2.read();
    force[i] = string;
    i++;
  }

  int sPos5 = atoi(force);
  Serial.println(sPos5);

  delay(100);
}