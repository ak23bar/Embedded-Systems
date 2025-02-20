
#include "motion_h.h"
#include <driverlib/rom_map.h>
#include <driverlib/gpio.h>
#include <driverlib/rom.h>
#include "launchpad.h"


typedef struct {
    Event *callback_event;
    uint32_t pin_value;
    bool new_input;
} MotionSensorState;

   MotionSensorState motion_sensor;
   void MotionISR();


void MotionInit() { // Initializing PIR motion sensor

    motion_sensor.callback_event = NULL;
    motion_sensor.new_input = false;


    // Enable Port C peripheral (from lab 4)
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Configure PC4 as output pin (from lab 4)
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);


        GPIOIntRegister(GPIO_PORTC_BASE, MotionISR);
        GPIOIntTypeSet (GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);
        IntPrioritySet (INT_GPIOC, 0); //set equal to 1 to enable interrupt
        GPIOIntEnable (GPIO_PORTC_BASE, GPIO_PIN_4);
}

void MotionEventRegister (Event* callback_event) {

    assert(EventInitialized(callback_event));
    motion_sensor.callback_event = callback_event;

}



void MotionISR() {

           uint32_t pin_value = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4);


             motion_sensor.pin_value = pin_value;
             motion_sensor.new_input = true;


           // Schedule callback event
           if (motion_sensor.callback_event != NULL)
               EventSchedule (motion_sensor.callback_event, EventGetCurrentTime());

           GPIOIntClear (GPIO_PORTC_BASE, GPIO_PIN_4); //clears for input
}






