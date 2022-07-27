/* EGR */

#include <hw_types.h>
#include <uartStdio.h>
#include "i2c.h"


char dataRevMode[] = {0x0};
char dataRead[10];
char dataIRStop[] = {0x1, 0b01111111};
char dataIRStart[] = {0x1, 0b11111111};
unsigned int byte;

int main() {

	initi2c();

	// configuration of register 3
	char dataConfig[] = {0x3, 0b01111111};
//	char *config = dataConfig;
	writetoi2c(0x38, dataConfig, 2, 1);
//	UARTprintf("aktueller Wert: 1 \n");


//	char *RevMode = dataRevMode;
//	char *read = dataRead;
//	char *IRStop = dataIRStop;
//	char *IRStart = dataIRStart;


	while (1)
	{

		writetoi2c(0x38, dataRevMode, 1, 0);
//		UARTprintf("aktueller Wert: 2 \n");


		readfromi2c(0x38, dataRead, 1, 1);
//		UARTprintf("aktueller Wert: 3 \n");

		byte = dataRead[0];
//		UARTprintf("aktueller Wert: 4 \n");

		UARTprintf(BYTETOBINARYPATTERN, BYTETOBINARY(byte));
		UARTprintf("\n");
//		UARTprintf("aktueller Wert: 5 \n");


		writetoi2c(0x38, dataIRStop, 2, 1);
//		UARTprintf("aktueller Wert: 6 \n");


	    //Wait
	    delay_ms(200);


		writetoi2c(0x38, dataIRStart, 2, 1);
//		UARTprintf("aktueller Wert: 7 \n");

	}
	return 0;
}
