#include "temp_sensor.h"
#include "ras.h"

/*
 * Global declarations
 */

// Temperature sensor reading states
typedef struct {
    Event *callback_event;      // the callback event for data processing
    uint32_t raw_data;          // the raw reading from the ADC connected to the sensor
    bool new_input;             // if any new data input is ready
} RotaryAngleState;

RotaryAngleState RA_sensor;

/*
 * Initialize ADC to use Tiva C's internal temperature sensor
 *
 * Resources: ADC0, sequence #0, special channel TS (temperature sensor)
 * Configurations: processor trigger, interrupt enabled, use step 0 only
 */
void RASInit()
{
    // Initialize sensor state in memory
    RA_sensor.callback_event = NULL;
    RA_sensor.new_input = false;

    // Enable the ADC0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // Configure ADC0's sequencer #1
    ADCSequenceConfigure(ADC0_BASE, 1 /* sequencer */, ADC_TRIGGER_PROCESSOR, 1 /* priority */);

    // Configure step 0 of sequencer 0 to use the temperature sensor, with
    // interrupt enable, as the end of the sequence
    ADCSequenceStepConfigure(ADC0_BASE, 1 /* sequencer */, 0 /* step */,
                             ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END);

    // Configure the interrupt system for RAS
    ADCIntRegister(ADC0_BASE, 1 /* sequencer */, RASSensorISR);
    ADCIntEnable(ADC0_BASE, 1 /* sequencer */);

    // Enable ADC0, sequencer 0
    ADCSequenceEnable(ADC0_BASE, 1 /* sequencer */);
}

/*
 * Trigger temperature reading
 */
void RASTriggerReading()
{
    // Trigger the sampling
    ADCProcessorTrigger(ADC0_BASE, 1 /* sequencer */);
}

/*
 * Check if any new data is ready (for I/O polling)
 */
bool RASDataReady()
{
    return RA_sensor.new_input;
}

/*
 * Read the current input from the temperature sensor
 */
float RASDataRead()
{
     // Convert the raw data to an angle between 0-180 degrees
     int angle = (RA_sensor.raw_data * 181) / 4096;

    // Reset new data ready flag and return the reading in Fahrenheit
      RA_sensor.new_input = false;
      return angle;
}

/*
 * Set callback event for temperature sensor ISR
 */
void RASEventRegister(Event *event)
{
    RA_sensor.callback_event = event;
}



