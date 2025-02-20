
#include "motion_h.h"

void MotionInit() { // Initializing PIR motion sensor

    // Enable Port C peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);


    // Configure PC4 as output pin
        GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);

}




