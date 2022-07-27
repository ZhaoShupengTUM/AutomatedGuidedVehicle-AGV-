/* EGR */

#include <hw_types.h>
#include <interrupt.h>
#include <hw_gpio_v2.h>
#include "Motorsteuerung.h"
#include "delay_ms.h"
#include <uartStdio.h>


volatile int speed = 100;
volatile int count = 0;
//volatile int count = 6;


//void myGPIO2IsrA(){
//	//
//	count++;
////	setSpeed(1, speed);
//	UARTPutNum(count);
//
//	//Loeschen der Interrupt-Flags
//	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS(0)) |= (1 << GPIO_PORT1_PIN2);
//}
//
//void myGPIO2IsrB(){
//	//
////	if (speed <= 25){
////		speed = 25;
////	}
////	else {
////		speed = speed - 5;
////	}
//	count--;
////	setSpeed(1, speed);
//	UARTPutNum(count);
//
//	//Loeschen der Interrupt-Flags
//	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS(1)) |= (1 << GPIO_PORT1_PIN4);
//}


int main() {


	//pinmuxing fuer taster auf steckplatz 1
	PinMuxing(CONF_PORT1_PIN2, 0, 1, 7);
	PinMuxing(CONF_PORT1_PIN4, 0, 1, 7);
	PinMuxing(CONF_PORT1_PIN6, 0, 1, 7);
	//Taster pin als Input
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4, 1);
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6, 1);


//	//initialisiere ARM Interrupt COntroller
//	IntAINTCInit();
//
//	//Globale Interruptsteuerung aktivieren
//	IntMasterIRQEnable();
//
//	//Lokale Interruptquelle aktivieren
//	IntSystemEnable(SYS_INT_GPIOINT2A);
//	IntSystemEnable(SYS_INT_GPIOINT2B);
//
//	//Registerung der Funktion myGPIO2Isr auf GPIO2-Interrupt
//	IntRegister(SYS_INT_GPIOINT2A, myGPIO2IsrA);
//	IntRegister(SYS_INT_GPIOINT2B, myGPIO2IsrB);
//
////	IntPrioritySet(SYS_INT_GPIOINT2A, 0, AINTC_HOSTINT_ROUTE_IRQ);
//
//	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET(0)) |= (1 << GPIO_PORT1_PIN2);
////	HWREG(SOC_GPIO_2_REGS + GPIO_LEVELDETECT(0)) |= (1 << GPIO_PORT1_PIN2);
//    HWREG(SOC_GPIO_2_REGS + GPIO_FALLINGDETECT) |= (1 << GPIO_PORT1_PIN2);
//	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET(1)) |= (1 << GPIO_PORT1_PIN4);
//	HWREG(SOC_GPIO_2_REGS + GPIO_LEVELDETECT(0)) |= (1 << GPIO_PORT1_PIN4);

	EHRPWMinitForDCMotor();
    initMotor(1);
    initMotor(2);

	while (1)
	{
//		setSpeed(1, speed);
//		speed = speed + 10;
//		delay_ms(2000);
//		speed = speed + 10;
//		setSpeed(1, speed);
//		delay_ms(2000);

		if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN2) == 0){
			speed += 5;
			if (speed >= 100){
				speed = 100;
			}
			setSpeed(1, speed);
			setSpeed(2, speed);
			delay_ms(200);
		}

		else if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN4) == 0){
			speed -= 5;
			if (speed <= 0){
				speed = 0;
			}
			setSpeed(1, speed);
			setSpeed(2, speed);
			delay_ms(200);
		}

		else if (EGR_PinRead(GPIO_PORT1_PIN6_MODUL, GPIO_PORT1_PIN6) == 0){


			HWREG(GPIO_H_BRUECKE_MOTOR1_1_MODUL + 0x13c) ^= (1 << GPIO_H_BRUECKE_MOTOR1_1) | (1 << GPIO_H_BRUECKE_MOTOR1_2);

			HWREG(GPIO_H_BRUECKE_MOTOR1_2_MODUL + 0x13c) ^= (1 << GPIO_H_BRUECKE_MOTOR2_1) | (1 << GPIO_H_BRUECKE_MOTOR2_2);

//
//			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_1_MODUL, GPIO_H_BRUECKE_MOTOR1_1, 0);
//			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_2_MODUL, GPIO_H_BRUECKE_MOTOR1_2, 1);
//			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_1_MODUL, GPIO_H_BRUECKE_MOTOR2_1, 1);
//			EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_2_MODUL, GPIO_H_BRUECKE_MOTOR2_2, 0);


			//PWM an Pin A von Motor 1 und 2 anlegen
			if (count % 2 != 0){
				configEHRPWM_A(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_B(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_A(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_B(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
			}


			if (count % 2 == 0){
				configEHRPWM_A(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_B(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_A(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
				configEHRPWM_B(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
			}
			count += 1;
			delay_ms(400);
		}

	}
	return 0;
}
