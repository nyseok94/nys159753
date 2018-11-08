#include <stdio.h>
#include <wiringPi.h>

#define SW1 1 // BCM_GPIO 18
#define LED1 29 // BCM_GPIO 29

int main() {

	int i;

	if(wiringPiSetup() == -1) return -1;

	pinMode(SW1, INPUT);
	pinMode(LED1, OUTPUT);
	for(;;){

		if(digitalRead(SW1) == 1){
			printf("Switch open LED OFF\n");
			digitalWrite(LED1, 0);
			delay(1000);
		}
		else {
			printf("Switch close LED ON\n");
			digitalWrite(LED1, 1);
			delay(1000);
		}
	}
	return 0;
}


