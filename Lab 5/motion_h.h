#ifndef MOTION_H_
#define MOTION_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include "launchpad.h"




void MotionInit (); // Initializing motion sensor
void MotionEventRegister (Event *callback_event); //Set callback event
int MotionDetected(); // Motion sensor detection
//void MotionISR();


#endif /* MOTION_H_ */
