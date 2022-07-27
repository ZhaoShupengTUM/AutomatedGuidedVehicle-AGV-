// Fuegt hier eure Funktionen zum Ansteuern der Motoren ein
#include "Motorsteuerung.h"



void initMotor(unsigned int MotorModule){
	//pinmuxing fuer MOTOR 1
	if (MotorModule == 1){
		PinMuxing(CONF_H_BRUECKE_MOTOR1_1, 1, 0, 7);
		PinMuxing(CONF_H_BRUECKE_MOTOR1_2, 1, 0, 7);
		PinMuxing(CONF_H_BRUECKE_MOTOR1_1, 1, 0, 6);
		PinMuxing(CONF_H_BRUECKE_MOTOR1_2, 1, 0, 6);

//		EHRPWMinitForDCMotor();

        EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, 0);

		//Forward mode
		EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_1_MODUL, GPIO_H_BRUECKE_MOTOR1_1, 1);
		EGR_PinWrite(GPIO_H_BRUECKE_MOTOR1_2_MODUL, GPIO_H_BRUECKE_MOTOR1_2, 0);

		//PWM an Pin A von Motor 1 anlegen
		configEHRPWM_A(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);
		configEHRPWM_B(SOC_EPWM_1_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);


	}
	else if (MotorModule == 2){
		PinMuxing(CONF_H_BRUECKE_MOTOR2_1, 1, 0, 7);
		PinMuxing(CONF_H_BRUECKE_MOTOR2_2, 1, 0, 7);
		PinMuxing(CONF_H_BRUECKE_MOTOR2_1, 1, 0, 4);
		PinMuxing(CONF_H_BRUECKE_MOTOR2_2, 1, 0, 4);

//		EHRPWMinitForDCMotor();

        EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, 0);

		EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_1_MODUL, GPIO_H_BRUECKE_MOTOR2_1, 0);
		EGR_PinWrite(GPIO_H_BRUECKE_MOTOR2_2_MODUL, GPIO_H_BRUECKE_MOTOR2_2, 1);

		configEHRPWM_A(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_LOW, EHRPWM_SET_OUTPUT_LOW);
		configEHRPWM_B(SOC_EPWM_2_REGS, EHRPWM_SET_OUTPUT_HIGH, EHRPWM_SET_OUTPUT_LOW);


	}
}

void setSpeed(unsigned int MotorModule, int Speed){

	if (MotorModule == 1){
		EHRPWMsetDutyCycle(SOC_EPWM_1_REGS, Speed);

	}
	else if (MotorModule == 2){
		EHRPWMsetDutyCycle(SOC_EPWM_2_REGS, Speed);
	}

}
