#ifndef __FORCE_H__

#include <Arduino.h>

#define FORCE_SENSOR_PIN 36
#define RESISTANCE 43000.00
#define VOLTAGE_INPUT_ESP32 3.0
#define ESP32_ADC_RANGE 4095

float bridgeDivider(float resistance, uint16_t ADC_measurement){
    float voltage_measurement = (float) ADC_measurement/ESP32_ADC_RANGE*VOLTAGE_INPUT_ESP32;
    return voltage_measurement*resistance/(VOLTAGE_INPUT_ESP32-voltage_measurement);
}

void setup(){
    Serial.begin(115200);
}


void loop(){
    uint16_t analogReading = analogRead(FORCE_SENSOR_PIN);
    float resistance = bridgeDivider(RESISTANCE,analogReading);
    Serial.print("ADC:\t");
    Serial.print(analogReading);
    Serial.print("\t\tResistance:\t");
    Serial.println(resistance);
    delay(500);
}


#endif