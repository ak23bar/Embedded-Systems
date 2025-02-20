/*
 * lab8_main.c: Starter code for ECE 266 Lab 8, main.c, fall 2024
 * Note: In this semester, a small part of starter code is provided
 * (none was provided before).
 *
 * Lab 8: Distance Measurement
 *
 * Created by Zhao Zhang
 * Last update: fall 2024
 * Edited by: Akbar Aman, David Mendoza, James Patel
 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "launchpad.h"
#include "seg7.h"
#include "ranger.h"

// Initial state of 7-segment display showing as "0000" with colon on
Seg7Display seg7 = { { 10, 10, 10, 10 }, false /* colon on */};

/*
 * Global variables
 */

// System state
typedef struct {
    enum {Millimeter, Inch} display_mode;       // display inch or millimeter
} SysState;

// The events
Event trigger_ranger_reading_event;
Event push_button_event;
Event clock_update_event;

SysState sys = {Millimeter};

/*******************************************
 * Task 1: Trigger and read the ranger
 ******************************************/

// Trigger the ranger reading every 1/2 second
void TriggerRangerReading(Event *event)
{

    RangerTriggerReading();
    uint32_t pulseWidth = RangerGetData();
    uint32_t distance;


    uprintf("Ranger reading: %u \r\n", (uint32_t)pulseWidth);

    if (sys.display_mode == Inch){
        seg7.colon_on = true;
        //Calculate the distance in inches based on the pulse width
        distance = (pulseWidth * 12) / 89657;
        //Calculate feet and inches
        uint32_t feet = distance / 12;
        uint32_t inches = distance % 12;

        // Sets to feet
        if (feet >= 10) {
            seg7.digit[3] = feet / 10;
            seg7.digit[2] = feet % 10;
        }

        else if (feet > 0) {
            seg7.digit[3] = 11;
            seg7.digit[2] = feet;
        }

        else if (feet == 0) {
            seg7.digit[3] = 11;
            seg7.digit[2] = 11;
        }

        // Set to inches
        if (inches < 10 && feet != 0) {
            seg7.digit[1] = 0;
        }

        else{
            seg7.digit[1] = inches / 10;
        }

        if ((inches < 10) && (feet == 0)){
            seg7.digit[1] = 11;
        }
        seg7.digit[0] = inches % 10;
    }


    else{
        //Calculate the distance based on the width
        distance = (pulseWidth * 304.8) / 89657;
        seg7.colon_on = false;
        seg7.digit[3] = distance / 1000 % 10;
        seg7.digit[2] = distance / 100 % 10;
        seg7.digit[1] = distance / 10 % 10;
        seg7.digit[0] = distance % 10;


        if (distance >= 9999){
            seg7.digit[3] = 9;
            seg7.digit[2] = 9;
            seg7.digit[1] = 9;
            seg7.digit[0] = 9;
        }

        else if(distance < 10){
            seg7.digit[3] = 11;
            seg7.digit[2] = 11;
            seg7.digit[1] = 11;
            seg7.digit[0] = distance % 10;
        }


        else if(distance < 100){
            seg7.digit[3] = 11;
            seg7.digit[2] = 11;
            seg7.digit[1] = distance / 10 % 10;
            seg7.digit[0] = distance % 10;
        }


        else if(distance < 1000){
            seg7.digit[3] = 11;
            seg7.digit[2] = distance / 100 % 10;
            seg7.digit[1] = distance / 10 % 10;
            seg7.digit[0] = distance % 10;
        }
    }


    // Update the seven-segment display
    Seg7Update(&seg7);



    EventSchedule(event, event->time + 500);
}



void CheckPushButton(Event *event)
{
     int input = PushButtonRead();
     switch (input)
     {
     //Pushbutton SW1 to display (mm) Mode
     case 1:

        sys.display_mode = Millimeter;
        break;

     //Pushbutton SW2 to display Inch Mode
     case 2:

         sys.display_mode = Inch;
         break;
         }
}




/*******************************************
 * The main function
 ******************************************/
void main(void)
{

    LaunchPadInit();
    RangerInit();
    Seg7Init();

    // Initialize the events
    EventInit(&trigger_ranger_reading_event, TriggerRangerReading);

    //call the ranger event
    RangerEventRegister(&trigger_ranger_reading_event);

    //check push button
    EventInit(&push_button_event, CheckPushButton);


    // Schedule time event
    EventSchedule(&trigger_ranger_reading_event, 100);

    //Register push button event
    PushButtonEventRegister(&push_button_event);

    // Loop forever
    while (true)
    {
        // Wait for interrupt
        asm("   wfi");

        // Execute scheduled callbacks
        EventExecute();
    }
}
