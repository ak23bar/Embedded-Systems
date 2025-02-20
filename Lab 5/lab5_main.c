/*
 * Lab 5 starter code
 * ECE 266, fall 2024
 *
 * lab4_main.c: Implement the tasks for a motion detection alarm.
 *
 * Created by Zhao Zhang
 * Edited by Akbar Aman and David Mendoza
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "launchpad.h"
#include "buzzer_h.h"
#include "motion_h.h"

/********************************************************************************
 * Global declarations
 *******************************************************************************/

// The data structure for the system state
typedef struct {
    // Activated state: if the system is activated or not
    bool activated;

    // Alert state: If the alert is on or off
    bool alerted;

    // Sound state: If the buzzer is turned on to make a sound or not
    // Note: When the system is activated and alerted, the buzzer is turned
    // on and off periodically
    bool buzzer_on;
} SysState;

// The system state
static SysState sys =
{
    false /* not activated */,
    false /* not alerted */,
    false /* buzzer not turned on */
};

// The events
Event buzzer_play_event;
Event check_push_button_event;
Event motion_detect_event;

/********************************************************************************
 * Task 1: If the system is activated and alerted, make the buzzer play
 * on/off sound. The buzzer will be repeatedly turned on and off.
 *
 * You may adjust the on and off times to change the sound pattern and intensity.
 *
 * Note: This is a callback function.
 *******************************************************************************/

void BuzzerPlay(Event *event)                   // the scheduled time
{
    uint32_t delay = 500;                       // default checking interval

    if (sys.alerted)
    {
        // Turn buzzer on and off
        if (sys.buzzer_on)
        {
            // The buzzer is on: turn it off
            BuzzerOff();
            sys.buzzer_on = false;
            delay = 2988;                       // off for 2988 ms
        }
        else
        {
            // The buzzer is off: turn it on
            BuzzerOn();
            sys.buzzer_on = true;
            delay = 12;                         // on for 12 ms
        }
    }
    else
    {
        // Make sure the buzzer is turned off
        if (sys.buzzer_on)
        {
            BuzzerOff();
            sys.buzzer_on = false;
        }
    }

    // schedule callback to buzzer play
    EventSchedule(event, event->time + delay);
}

/********************************************************************************
 * Task 2: YOUR CODE, check the motion sensor
 *
 * Check the motion sensor input. If motion is detected, put the system
 * in the alerted state. Otherwise, put it in the non-alerted state.
 *
 * This is a callback function. In the next lab, you will re-write this function
 * to make it interrupt based.
 *******************************************************************************/
void MotionDetect(Event* event) {
    // Check if the system is activated
    if (sys.activated) {
        // Call the MotionDetected function to check for motion
        int motion = MotionDetected();

        // If motion is detected (motion is not equal to 0)
        if (motion != 0) {
            // Print message indicating motion is being detected
            printf("%s\n\r", "Motion is being detected!");
        }

        // Update the alerted status based on motion detection
        sys.alerted = motion != 0;

        // If alerted, turn on the red LED; otherwise, turn on the green LED
        if (sys.alerted) {
            LedTurnOnOff(true /* red */, false /* blue */, false /* green */);
        } else {
            LedTurnOnOff(false /* red */, false /* blue */, true /* green */);
        }
    }
}

/********************************************************************************
 * Task 3: Check push buttons.
 *
 * In the starter code: Pushing SW1 activates the system and put it in the
 * alerted state. Pushing SW2 deactivates the system.
 *
 * IN YOUR SOLUTION CODE: Pushing SW1 activates the system. Pushing SW2
 * deactivates the system. If the system is activated, the motion sensor
 * input decides if the system is put in the alerted state or not.
 *
 * This function is called upon interrupts. It is NOT a callback function.
 *
 * YOU NEED TO REVISE THIS FUNCTION
 *
 *******************************************************************************/

void CheckPushButton(Event *event)
{
    int code = PushButtonRead();        // read the pushbutton
    switch (code)
    {
    case 1:                     // SW1 is pushed
        if (!sys.activated)
        {
            // Activate the system
            sys.activated = true;
            LedTurnOnOff(false /* red */, false /* blue */, true /* green */);
        }
        break;

    case 2:                     // SW2 is pushed
        if (sys.activated)
        {
            // De-activate the system and turn off LED
            sys.activated = false;
            sys.alerted = false;
            LedTurnOnOff(false /* red */, false /* blue */, false /* green */);
        }
        break;
    }
}


/********************************************************************************
 * The main function: Print out a message, schedule the first callback event(s),
 * and then run the callback scheduler.
 *******************************************************************************/

int main(void)
{
    // Initialize the Tiva C LaunchPad and 7-seg
    LaunchPadInit();
    BuzzerInit();
    MotionInit();

    printf("%s\n\r", "Lab 5: Motion Detection Alarm");

    // Initialize the event objects
    EventInit(&buzzer_play_event, BuzzerPlay);
    EventInit(&check_push_button_event, CheckPushButton);
    EventInit(&motion_detect_event, MotionDetect);

    // Register ISR event
    PushButtonEventRegister(&check_push_button_event);
    MotionEventRegister(&motion_detect_event);
    // Schedule time events
    EventSchedule(&buzzer_play_event, 100);

    // Run the callback scheduler
    while (true)
    {
        // Wait for interrupt events (include callback events)
        asm("   wfi");

        // Run callback events
        EventExecute();
    }
}
