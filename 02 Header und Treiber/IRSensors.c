// Verlinkt
#include "IRSensors.h"

void initIRSensor()
{

	initi2c();

	// configuration of register 3
	char dataConfig[] = {0x3, 0b01111111};
	//	char *config = dataConfig;
	writetoi2c(0x38, dataConfig, 2, 1);

}



unsigned int readIRSensor()
{
	char dataRevMode[] = {0x0};
	char dataRead[10];
	char dataIRStop[] = {0x1, 0b01111111};
	char dataIRStart[] = {0x1, 0b11111111};
	unsigned int byte;
	while (1)
	{
		writetoi2c(0x38, dataRevMode, 1, 0);

		readfromi2c(0x38, dataRead, 1, 1);

		byte = dataRead[0];

		//	UARTprintf(BYTETOBINARYPATTERN, BYTETOBINARY(byte));
		//	UARTprintf("\n");

		writetoi2c(0x38, dataIRStop, 2, 1);

		//Wait
		delay_ms(200);

		writetoi2c(0x38, dataIRStart, 2, 1);

		return byte;

	}
}
