/* EGR */

#include <hw_types.h>

int main() {
	//pinmuxing
	HWREG(0x44e10000 + 0x8b8) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode
	HWREG(0x44e10000 + 0x8b8) |= 0x7; // set new mode GPIO

	//LED pin als output schalten
	HWREG(0x481ac000 + 0x134) &= ~(1 << 12); // basic adress is GPIO2, offset is GPIO_OE, enable output

	//LED anschalten(pin abschalten)
	HWREG(0x481ac000 + 0x13c) &= ~(1 << 12); // set GPIO_DATAOUT to 0



	while (1)
	{
		//LED anschalten(pin abschalten)
		HWREG(0x481ac000 + 0x13c) &= ~(1 << 12); // set GPIO_DATAOUT to 0

	}
	return 0;
}
