A simpler structure of main.cpp\\ \\

/*
void setup() {
	Serial.begin(115200);
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
  
  servo1.attach(S1, 1000, 2000); 
  servo2.attach(S2, 1000, 2000);
  servo3.attach(S3, 1000, 2000);
  servo4.attach(S4, 1000, 2000);
  servo5.attach(S5, 1000, 2000);
}

void loop() {
  
  force1 = analogRead(FF1);
  force2 = analogRead(FF2);
  force3 = analogRead(FF3);
  force4 = analogRead(FF4);
  force5 = analogRead(FF5);
  
	if(force1 > 220){ 
    j += ((force1 - 200)/20);
	} else if (force1 < 180) {
    j -= ((200 - force1)/20);
	}

  if(j>2000) j = 2000;
  if(j<1000) j = 1000;
    
  servo1.write(j);
	Serial.println(force1);
  Serial.println(j);
	delay(2);

}
*/