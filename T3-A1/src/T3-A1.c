/* EGR */
#include <hw_tsc_adc_ss.h>
#include <hw_types.h>
#include <soc_AM335x.h>
#include <uartStdio.h>
#include "delay_ms.h"

unsigned int meinAdcWert;

int main() {

	// Clock aktivieren
	HWREG(SOC_CM_WKUP_REGS + (0xbc)) &= ~(0b11);
	HWREG(SOC_CM_WKUP_REGS + (0xbc)) |= (1<<1);

	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 2);

	// ein step aktivieren
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 1);

	// Step einstellen
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~(0b11);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 0);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 4);
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~((1 << 12) | (1 << 13) | (1 << 14));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (1 << 19);  //PORT 1
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) &= ~(1 << 26);

	// ADC enable
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 0);


	while (1)
	{
		meinAdcWert = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));
		UARTprintf("aktueller Wert: %d \n", meinAdcWert);
		delay_ms(2000);

	}
	return 0;
}
