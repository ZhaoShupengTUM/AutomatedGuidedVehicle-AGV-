/* EGR */

#include <hw_types.h>
#include "delay_ms.h"

int main() {
	/* steckplatz 1 for taster using GPIO2---------------------------------*/
	  //pinmuxing
	HWREG(0x44e10000 + 0x8b8) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_6
	HWREG(0x44e10000 + 0x8b8) |= 0x7; // set new mode GPIO
	HWREG(0x44e10000 + 0x8b0) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_4
	HWREG(0x44e10000 + 0x8b0) |= 0x7; // set new mode GPIO
	HWREG(0x44e10000 + 0x8a8) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_2
	HWREG(0x44e10000 + 0x8a8) |= 0x7; // set new mode GPIO
	  //pullup enable
	HWREG(0x44e10000 + 0x8b8) &=~ (1<<3); // 2rd
	HWREG(0x44e10000 + 0x8b0) &=~ (1<<3); // 4th
	HWREG(0x44e10000 + 0x8a8) &=~ (1<<3); // 6th
	  //pullup set
	//HWREG(0x44e10000 + 0x8b8) &=~ (1<<4); // 2rd
	HWREG(0x44e10000 + 0x8b8) |= (1<<4);
	//HWREG(0x44e10000 + 0x8b0) &=~ (1<<4); // 4th
	HWREG(0x44e10000 + 0x8b0) |= (1<<4);
	//HWREG(0x44e10000 + 0x8b0) &=~ (1<<4); // 6th
	HWREG(0x44e10000 + 0x8a8) |= (1<<4);

	//2rd pin als input schalten(GPIO2)
	//HWREG(0x481ac000 + 0x134) &=~ (1 << 12); // delete old selection
	HWREG(0x481ac000 + 0x134) |= (1 << 12); // set 2rd pin as input

	//4th pin als input schalten
	//HWREG(0x441ac000 + 0x134) &=~ (1 << 10); // delete old selection
	HWREG(0x481ac000 + 0x134) |= (1 << 10); // set 4th pin as input

	//6th pin als input schalten
	//HWREG(0x441ac000 + 0x134) &=~ (1 << 8); // delete old selection
	HWREG(0x481ac000 + 0x134) |= (1 << 8); // set 6th pin as input


	/* steckplatz 2 for LED using GPIO0 ------------------------------------*/
	//pinmuxing
	HWREG(0x44e10000 + 0x8d8) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_14
	HWREG(0x44e10000 + 0x8d8) |= 0x7; // set new mode GPIO
	HWREG(0x44e10000 + 0x8d4) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_13
	HWREG(0x44e10000 + 0x8d4) |= 0x7; // set new mode GPIO
	HWREG(0x44e10000 + 0x8d0) &=~ ((1<<0)|(1<<1)|(1<<2)); // delete old mode for lcd_data_13
	HWREG(0x44e10000 + 0x8d0) |= 0x7; // set new mode GPIO

	//LED 2rd pin als output schalten(GPIO2)
	HWREG(0x44e07000 + 0x134) &= ~(1 << 10); // offset is GPIO_OE, enable output
	//LED anschalten(pin abschalten)
	HWREG(0x44e07000 + 0x13c) &= ~(1 << 10); // set GPIO_DATAOUT to 0

	//LED 4th pin als output schalten
	HWREG(0x44e07000 + 0x134) &= ~(1 << 9); // offset is GPIO_OE, enable output
	//LED anschalten(pin abschalten)
	HWREG(0x44e07000 + 0x13c) &= ~(1 << 9); // set GPIO_DATAOUT to 0

	//LED 4th pin als output schalten
	HWREG(0x44e07000 + 0x134) &= ~(1 << 8); // offset is GPIO_OE, enable output
	//LED anschalten(pin abschalten)
	HWREG(0x44e07000 + 0x13c) &= ~(1 << 8); // set GPIO_DATAOUT to 0


	while (1)
	{
		if (((HWREG(0x481ac000 + 0x138)>>12) & 1) == 0){

			HWREG(0x44e07000 + 0x13c) &= ~(1 << 10);
			delay_ms(200);
			HWREG(0x44e07000 + 0x13c) |= (1 << 10);

		}
		else if (((HWREG(0x481ac000 + 0x138)>>10) & 1) == 0){

			HWREG(0x44e07000 + 0x13c) &= ~(1 << 9);
			delay_ms(200);
			HWREG(0x44e07000 + 0x13c) |= (1 << 9);

		}
		else if (((HWREG(0x481ac000 + 0x138)>>8) & 1) == 0){

			HWREG(0x44e07000 + 0x13c) &= ~(1 << 8);
			delay_ms(200);
			HWREG(0x44e07000 + 0x13c) |= (1 << 8);

		}

	}
	return 0;
}
