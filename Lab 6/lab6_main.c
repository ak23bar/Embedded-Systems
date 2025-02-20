/*
 * Starter code for ECE 266 Lab 6, main.c, fall 2024
 *
 * Lab 6: Temperature reading and knob input (ADC)
 *
 * Created by Zhao Zhang
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "launchpad.h"
#include "seg7.h"
#include "temp_sensor.h"
#include "ras.h"

// The events
Event ts_trigger_event;
Event ts_data_event;
Event ras_trigger_event;
Event ras_data_event;

Seg7Display seg7 = { { 0, 0, 0, 0 }, false }; // initial state is "0000" with colon off
/*
 * Trigger the temperature reading periodically
 */

void TriggerTemperatureReading(Event *event)
{
    // Trigger ADC sampling for the temperature sensor
    TsTriggerReading();

    // Schedule the next callback in 4000 milliseconds
    EventSchedule(event, event->time + 4000);
}

void RotaryAngleSensorTriggerReading (Event *event)
{
    //Triggers the Rotary Angle Sensor Reading
    RASTriggerReading();

    //Schedule the next callback in 2000 milliseconds
    EventSchedule(event, event->time + 4000);

}


/*
 * Process temperature reading data
 */
void ProcessTemperatureReading(Event *event)
{
    float temp_F = TsDataRead();
    int temp10 = temp_F * 10;

    // Print on terminal
    printf("Temperature Reading Sensor: %u.%u \r\n", temp10 / 10, temp10 % 10);

    //Print on Seg7
    int tempInt = (int) temp_F;

    seg7.digit[0] = 10; // this digit is not used
    seg7.digit[1] = temp10 % 10;
    seg7.digit[2] = (tempInt % 10);
    seg7.digit[3] = ((tempInt / 10) % 10);
    seg7.colon_on = true;   //Turn on colon
    Seg7Update(&seg7);

}

void ProcessRASReading (Event *event)
{
    int angle = RASDataRead();
    int fangle = angle;
    seg7.digit[0] = fangle % 10;
    seg7.digit[1] = fangle/10 % 10;
    seg7.digit[2] = fangle/100 % 10;
    seg7.digit[3] = 10;     //this digit is not used
    seg7.colon_on = false;  //Turn off colon
    Seg7Update(&seg7);
    printf("RAS Reading: %d degrees\r\n", angle);
}

/*
 * The main function: Initialize the system and run event scheduler loop
 */
int main(void)
{
    // Initialize all hardware components being used
    LaunchPadInit();
    TsInit();



    // Initialize and schedule timing events
    EventInit(&ts_trigger_event, TriggerTemperatureReading);
    EventSchedule(&ts_trigger_event, 100);

    // Initialize and register ISR events
    EventInit(&ts_data_event, ProcessTemperatureReading);
    TsEventRegister(&ts_data_event);

    // Initialize all hardware components being used
    RASInit();
    Seg7Init();

    // Initialize and schedule timing events
    EventInit(&ras_trigger_event, RotaryAngleSensorTriggerReading);
    EventSchedule(&ras_trigger_event, 2100);

    // Initialize and register ISR events
    EventInit(&ras_data_event, ProcessRASReading);
    RASEventRegister(&ras_data_event);

    printf("%s\n\r", "Lab 6: Ambient Sensing (ADC)");

    // Loop forever
    while (true)
    {
        // Wait for interrupt to happen
        __asm("    wfi");

        // Call the callback scheduler
        EventExecute();
    }
}
