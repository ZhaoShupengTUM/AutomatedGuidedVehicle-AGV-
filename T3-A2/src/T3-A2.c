/* EGR */

#include <hw_tsc_adc_ss.h>
#include <hw_types.h>
#include <soc_AM335x.h>
#include <uartStdio.h>
#include "delay_ms.h"

unsigned int meinAdcWert_1;
unsigned int meinAdcWert_2;

int main() {

	HWREG(SOC_CM_WKUP_REGS + (0xbc)) &= ~(0b11);
	HWREG(SOC_CM_WKUP_REGS + (0xbc)) |= (1<<1);

	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 2);

	// zwei Steps aktivieren
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 1);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 2);

	// Step 1 einstellen
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~(0b11);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 0);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 4);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 12) | (1 << 13) | (1 << 14));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 19);  //PORT 1
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~(1 << 26);


	// Step 2 einstellen
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~(0b11);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 0);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 4);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 12) | (1 << 13) | (1 << 14));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 19);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 20);  //PORT 2
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 26);



	// ADC enable
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 0);


	while (1)
	{
		meinAdcWert_1 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));
		meinAdcWert_2 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(1));
		UARTprintf("aktueller Wert 1: %d, aktueller Wert 2: %d \n", meinAdcWert_1, meinAdcWert_2);

//		UARTprintf("aktueller Wert 2: %d \n", meinAdcWert_2);
		delay_ms(500);

	}
	return 0;
}
