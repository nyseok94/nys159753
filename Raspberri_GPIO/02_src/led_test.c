#include <stdio.h>
#include <wiringPi.h>

#define LED1 29 // BCM_GPIO 21

int main(){

	int i;
	if(wiringPiSetup() == -1) return -1;

	pinMode(LED1, OUTPUT);
	for(i=0; i < 5; i++){

		digitalWrite(LED1, 1);
		delay(500);
		digitalWrite(LED1, 0);
		delay(500);
	}

	return 0;

}	
