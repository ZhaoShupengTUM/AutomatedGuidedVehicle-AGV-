/* EGR */

#include <hw_types.h>
#include <uartStdio.h>
#include "IRSensors.h"
#include "Motorsteuerung.h"

char dataRevMode[] = {0x0};
char dataRead[10];
char dataIRStop[] = {0x1, 0b01111111};
char dataIRStart[] = {0x1, 0b11111111};

unsigned int byte;

int fir_num = 0;
int snd_num = 0;
int trd_num = 0;

volatile int speed = 100;

void forward(int speed)
{
	setSpeed(1, speed);
	setSpeed(2, speed);
}

void turn(int speed_left, int speed_right)
{
	setSpeed(1, speed_left);
	setSpeed(2, speed_right);
}


int main() {

	EHRPWMinitForDCMotor();
    initMotor(1);
    initMotor(2);

    initIRSensor();


	while (1)
	{
		writetoi2c(0x38, dataRevMode, 1, 0);

		readfromi2c(0x38, dataRead, 1, 1);

		byte = dataRead[0];

//		UARTprintf(BYTETOBINARYPATTERN, BYTETOBINARY(byte));
//		UARTprintf("\n");

		writetoi2c(0x38, dataIRStop, 2, 1);

		//Wait
		delay_ms(10);

		writetoi2c(0x38, dataIRStart, 2, 1);


		fir_num = byte & 0x40 ? 1 : 0;
		snd_num = byte & 0x20 ? 1 : 0;
		trd_num = byte & 0x10 ? 1 : 0;

		if (fir_num == 0){
			turn(0, 50);

		}

		if (trd_num == 0){
			turn(50, 0);
		}

		if ((snd_num == 0) && (fir_num == 1) && (trd_num == 1)){
			forward(50);
		}
	}
	return 0;
}
