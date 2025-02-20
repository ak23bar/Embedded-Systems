#ifndef MOTION_H_
#define MOTION_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>


void MotionInit (); // Initializing motion sensor

bool MotionDetected(); // Motion sensor detection


#endif /* MOTION_H_ */
