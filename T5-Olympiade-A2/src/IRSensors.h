// Verlinkt
#ifndef IRSensor_H_
#define IRSensor_H_
#include <hw_types.h>
#include <uartStdio.h>
#include "i2c.h"


void initIRSensor();

unsigned int readIRSensor();

#endif
