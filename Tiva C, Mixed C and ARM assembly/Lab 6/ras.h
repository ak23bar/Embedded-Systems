/*
 * temp_sensor.h: Starter code for ECE 266 Lab 6, spring 2024
 *
 * Temperature sensor module
 *
 * Created by Zhao Zhang, fall 2022
 * Last update: Feb. 18, 2024
 */

#ifndef RA_SENSOR_H_
#define RA_SENSOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inc/hw_memmap.h>
#include <inc/hw_ints.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/adc.h>
#include "launchpad.h"

// Initialize ADC to use Tiva C's internal temperature sensor
void RASInit();

// Trigger temperature reading
void RASTriggerReading();

// Check if any new reading is ready (for I/O polling)
bool RASDataReady();

// Return temperature reading in Fahrenheit
float RASDataRead();

// Set callback event for temperature sensor ISR
void RASEventRegister(Event *event);

// The ISR function
void RASSensorISR();

#endif /* RA_SENSOR_H_ */
