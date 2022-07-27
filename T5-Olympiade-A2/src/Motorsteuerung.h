// Fuegt hier die Header-Daten zu euren Funktionen ein
#ifndef Motorsteuerung_H_
#define Motorsteuerung_H_

#include <soc_AM335x.h>
#include "EGR_Cape.h"
#include "GPIO.h"
#include "Conf_mod.h"
#include "EGR_DCMotor.h"


void initMotor(unsigned int MotorModule);
void setSpeed(unsigned int MotorModule, int Speed);


#endif
