/* EGR */

#include <hw_tsc_adc_ss.h>
#include <hw_types.h>
#include <soc_AM335x.h>
#include <uartStdio.h>
#include <hw_gpio_v2.h>
#include "Motorsteuerung.h"
#include "delay_ms.h"


unsigned int meinAdcWert_1;
unsigned int meinAdcWert_2;
unsigned int speed = 0;
unsigned int speed_left = 0;
unsigned int speed_right = 0;


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

	EHRPWMinitForDCMotor();
    initMotor(1);
    initMotor(2);


	while (1)
	{
		meinAdcWert_1 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));
		meinAdcWert_2 = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(1));

		if (meinAdcWert_2 < 1500){
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_1_MODUL, GPIO_H_BRUECKE_MOTOR1_1, 1);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_2_MODUL, GPIO_H_BRUECKE_MOTOR1_2, 0);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_1_MODUL, GPIO_H_BRUECKE_MOTOR2_1, 0);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_2_MODUL, GPIO_H_BRUECKE_MOTOR2_2, 1);
			//PWM an Pin A von Motor 1 anlegen
			configEHRPWM_A(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);

			configEHRPWM_A(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);

			if (meinAdcWert_1 > 2500) {
				speed_left = ((1 - meinAdcWert_2 / 1500.0) * 100) - 20;
				speed_right = ((1 - meinAdcWert_2 / 1500.0) * 100);
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed_left);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed_right);
			}
			else if (meinAdcWert_1 < 1500) {
				speed_left = ((1 - meinAdcWert_2 / 1500.0) * 100);
				speed_right = ((1 - meinAdcWert_2 / 1500.0) * 100) - 20;
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed_left);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed_right);
			}
			else {
				speed = ((1 - meinAdcWert_2 / 1500.0) * 100);
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed);
			}
		}
		else if (meinAdcWert_2 > 2200){
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_1_MODUL, GPIO_H_BRUECKE_MOTOR1_1, 0);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_2_MODUL, GPIO_H_BRUECKE_MOTOR1_2, 1);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_1_MODUL, GPIO_H_BRUECKE_MOTOR2_1, 1);
			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_2_MODUL, GPIO_H_BRUECKE_MOTOR2_2, 0);

			configEHRPWM_A(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_A(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);

			speed = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100;

			if (meinAdcWert_1 > 2500) {
				speed_left = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100 - 20;
				speed_right = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100;
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed_left);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed_right);
			}
			else if (meinAdcWert_1 < 1500) {
				speed_left = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100;
				speed_right = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100 - 20;
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed_left);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed_right);
			}
			else {
				speed = (meinAdcWert_2 - 2200.0) / (4000.0 - 2200.0) * 100;
				EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, speed);
				EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, speed);
			}
		}
		else {
			EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, 0);
			EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, 0);
		}

//		UARTprintf("speed left is: %d, speed right is: %d \n", speed_left, speed_right);

//		UARTprintf("aktueller Wert 2: %d \n", meinAdcWert_2);
		delay_ms(200);

	}
	return 0;
}
