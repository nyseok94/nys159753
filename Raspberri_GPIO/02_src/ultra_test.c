#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define trig 28 // BCM 20
#define echo 29 // BCM 21

int main() {

	int start_time, end_time;
	float distance;

	if(wiringPiSetup() == -1) return -1;

	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);

	while(1) {
		
		digitalWrite(trig, LOW);
		delay(500);
		digitalWrite(trig, HIGH);
		delayMicroseconds(10);
		digitalWrite(trig, LOW);

		while (digitalRead(echo) == 0);
		start_time = micros();
		while (digitalRead(echo) == 1);
		end_time = micros();
		distance = (end_time - start_time) / 29. / 2. ;
		ptinrf("Distance is %.2f cm\n", distance);
	}
	return 0;

}


