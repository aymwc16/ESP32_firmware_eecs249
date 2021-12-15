/*
 * Remote Feelings: Adam Curtis, Aymeric Wang, Xinying Hu
 * 11/30/21
 * Prototype version. Author: Adam Curtis, Aymeric Wang
 */
//adam made a change
#include <ESP32Servo.h>
#include <Arduino.h>
#include "calibration.h"
#include "pin_config.h"
#include "sender.h"
#include "reciever.h"
#include "MotionFuncs.h"
#include "constants.h"
//#include "adc.h"


int listSize = 100;
bool calibrated = false;

void robotControl(){
  /**a try-catch statement allows to deal with concurrent
   * access to UART. when that happens an error should be
   * sent but we disregard it. It's a bit dirty but it works!
   * */
  try {
    Pos_offset = 5 + scaleFactor(); //Get force from robot and scales it
    //followFingers();
    followFingersAverage();
    int average_position = averageFingerPos();
    Serial.println(String("Average position:\t")+String(average_position));
    send_control(average_position);
  }
  catch(...){}
}

void controller();

void setup() {
	Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1,RXp2,TXp2);
  
  for(int i = 0; i < 5; i++){
    avg_force[i] = construct_moving_average(listSize);
  }
  for(int j = 0; j < listSize; j++){
    for(int i = 0; i < 5; i++){
      forceAverage[i] = update_moving_average_value(avg_force[i], analogRead(FFPins[i]));
    }
  }


  //----Setting servos----
  setupServos();
  delay(200);
  calibrateForceZero();
  delay(1000);
}

void loop() {

  if (PLATFORM == 2){
    reference_forces_list_generator();
    robotControl();
    for(int i = 0; i < 5; i++){
      forceAverage[i] = update_moving_average_value(avg_force[i], analogRead(FFPins[i]));
    }
    int long bright_calculator = 0;
    for(int i = 0; i < 5; i++){
      bright_calculator += int((forceAverage[i]-restForce[i]));
    }
    bright_calculator = int(abs(bright_calculator)/5);
    uint8_t brightness = int(abs(bright_calculator));
    Serial.println(brightness);
    analogWrite(LOGOLED,brightness);
  }
  else{
    int position_recieved = force_message_reciever();
    if (position_recieved!=0) {
      int adc_command = MIN_PULSE_WIDTH;
      float alpha = (MAX_PULSE_WIDTH-MIN_PULSE_WIDTH)/1000;
      float sum = (position_recieved-1000);
      adc_command = adc_command + int(sum*alpha);
      Serial.println(String("Position:\t")+String(position_recieved));
      Serial.println(String("ADC command:\t")+String(adc_command));
      
      if (adc_command<(1250)){
        Servos[3].write(1250);
      }
      else if (adc_command>(2000)){
        Servos[3].write(2000);
      }
      else {
        Servos[3].write(adc_command);
      }
      
      forceAverage[0] = update_moving_average_value(avg_force[0], analogRead(FFPins[0]));
      long int local_force = forceAverage[0];
      send_control(local_force);
    }
  }
}