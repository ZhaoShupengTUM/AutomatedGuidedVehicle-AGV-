/* EGR */

#include <hw_types.h>
#include "delay_ms.h"
#include "EGR_Cape.h"
#include "GPIO.h"
#include "Conf_mod.h"

int main() {
	//pinmuxing fuer LEDs auf steckplatz 2
	PinMuxing(0x8d8, 1, 0, 7);
	PinMuxing(0x8d4, 1, 0, 7);
	PinMuxing(0x8d0, 1, 0, 7);
	PinMuxing(0x8c0, 1, 0, 7);

	//pinmuxing fuer taster auf steckplatz 1
	PinMuxing(0x8b8, 0, 1, 7);
	PinMuxing(0x8b0, 0, 1, 7);
	PinMuxing(0x8a8, 0, 1, 7);
	//Taster pin als Input
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6, 1);

	//set Delay
	unsigned int delay = 500;


	while (1)
	{
		// Wert lesen aus Taster 1 auf steckplatz 1
		unsigned int status_taster_1 = EGR_PinRead (GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2);
		// Wert lesen aus Taster 2 auf steckplatz 1
		unsigned int status_taster_2 = EGR_PinRead (GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4);
		// Wert lesen aus Taster 3 auf steckplatz 1
		unsigned int status_taster_3 = EGR_PinRead (GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);

		while (status_taster_1 == 0) {
			//LEDs nacheinader 500ms leuchten
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, 0);
			delay_ms(delay);
			status_taster_3 = EGR_PinRead (GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);
			while (status_taster_3 == 0){
				EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, 0);
			}
			EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, 1);
			EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, 0);
			delay_ms(delay);
			status_taster_3 = EGR_PinRead (GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);
			while (status_taster_3 == 0){
				EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN4, 0);
			}
			EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, 1);
			EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, 0);
			delay_ms(delay);
			status_taster_3 = EGR_PinRead (GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);
			while (status_taster_3 == 0){
				EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN6, 0);
			}
			EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, 1);
			EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, 0);
			delay_ms(delay);
			status_taster_3 = EGR_PinRead (GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);
			while (status_taster_3 == 0){
				EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN8, 0);
			}
			EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, 1);

			//status_taster_1 = EGR_PinRead (GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2);
			status_taster_2 = EGR_PinRead (GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4);

			if (status_taster_2 == 0){

				//LEDs nacheinader 200ms leuchten
				delay = 200;

			}

			else if (status_taster_2 == 1){

				delay = 500;

			}

//			if (status_taster_1 == 1){
//				//alle LEDs aus
//				EGR_PinWrite(GPIO_PORT2_PIN2_MODUL, GPIO_PORT2_PIN2, 1);
//				EGR_PinWrite(GPIO_PORT2_PIN4_MODUL, GPIO_PORT2_PIN4, 1);
//				EGR_PinWrite(GPIO_PORT2_PIN6_MODUL, GPIO_PORT2_PIN6, 1);
//				EGR_PinWrite(GPIO_PORT2_PIN8_MODUL, GPIO_PORT2_PIN8, 1);
//			}
		}

	}
	return 0;
}
