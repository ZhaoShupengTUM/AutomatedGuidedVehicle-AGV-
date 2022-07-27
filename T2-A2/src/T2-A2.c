/* EGR */

#include <hw_types.h>
#include <interrupt.h>
#include <soc_AM335x.h>
#include <hw_dmtimer.h>
#include "delay_ms.h"
#include "EGR_Cape.h"
#include "GPIO.h"
#include "Conf_mod.h"
#include "delay_ms.h"
#include <uartStdio.h>


unsigned long timer_startwert = 0xFFFFFFFF - 480000;
unsigned long timer_comparewert = 0xFFFFFFFF - 480000 + 36000;
unsigned long LOAD_VALUE = 0xFFFFFFFF - 480000;

void myTimer2Isr(){
	//Abfrage der Interruptquelle
	if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << 1)) != 0){
		//
		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, 1);

		//Loeschen der Interrupt-Flags
		HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << 1);
	}
	if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << 0)) != 0){
		//
		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL, GPIO_PORT3_PIN2, 0);

		//Loeschen der Interrupt-Flags
		HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << 0);


	}
}



int main() {
	//pinmuxing fuer Servomotor auf steckplatz 3
	PinMuxing(CONF_PORT3_PIN2, 1, 0, 7);

	//pinmuxing fuer taster auf steckplatz 1
	PinMuxing(CONF_PORT1_PIN2, 0, 1, 7);
	PinMuxing(CONF_PORT1_PIN4, 0, 1, 7);
	PinMuxing(CONF_PORT1_PIN6, 0, 1, 7);
	//Taster pin als Input
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6, 1);

    //EGR_PinWrite(SOC_GPIO_3_REGS, GPIO_PORT3_PIN2, 1);

    //Timer Konfigurieren-----------------------------------------------------------------------------------
	//Control Register des DMTimer 2 beschreiben
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) &= ~(1 << 0);

    HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) &=  ~(1 << 5);
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 1);

	//Timerwert direkt setzen
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = timer_startwert;

	//Timer load register
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR) = LOAD_VALUE;

	//TImer Compare register
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 6);
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = timer_comparewert;

	//initialisiere ARM Interrupt Controller
	IntAINTCInit();

	//Globale Interruptsteuerung aktivieren
	IntMasterIRQEnable();

	//Lokale Interruptquelle aktivieren
	IntSystemEnable(SYS_INT_TINT2);

	//Registerung der Funktion
	IntRegister(SYS_INT_TINT2, myTimer2Isr);

	//Ausloeser fuer einen Interrupt
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) &= ~(1 << 0) | (1 << 1) | (1 << 2);
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) |= (1 << 0) | (1 << 1);

	//Timer starten
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1 << 0);

//	EGR_PinWrite(SOC_GPIO_3_REGS, GPIO_PORT3_PIN4, 1);
//	EGR_PinWrite(SOC_GPIO_3_REGS, GPIO_PORT3_PIN6, 1);
//	EGR_PinWrite(SOC_GPIO_3_REGS, GPIO_PORT3_PIN8, 1);

	while (1)
	{
//		UARTPutNum(HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR));
//		UARTprintf("\r\n");
//		UARTPutNum(HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR));
//		UARTprintf("\r\n");
//		UARTPutNum(HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR));
//		UARTprintf("\r\n");

//		// Wert lesen aus Taster 1 auf steckplatz 1
//		unsigned int status_taster_1 = EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2);
//		// Wert lesen aus Taster 2 auf steckplatz 1
//		unsigned int status_taster_2 = EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4);
//		// Wert lesen aus Taster 3 auf steckplatz 1
//		unsigned int status_taster_3 = EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6);

		if (EGR_PinRead(GPIO_PORT1_PIN2_MODUL, GPIO_PORT1_PIN2) == 0){
			timer_comparewert -= 3000;
			delay_ms(200);
		}
		else if (EGR_PinRead(GPIO_PORT1_PIN4_MODUL, GPIO_PORT1_PIN4) == 0){
			timer_comparewert += 3000;
			delay_ms(200);
		}
		else if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6) == 0){
			timer_comparewert = 0xFFFFFFFF - 480000 + 36000;
			delay_ms(200);
		}

		HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = timer_comparewert;
	}
	return 0;
}
