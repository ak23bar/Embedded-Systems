# ECE 266: Embedded Systems

This repository contains all major lab assignments as well as my final project completed for Embedded Systems. The course focused on mixed C and ARM assembly programming for microcontrollers, embedded design principles, hardware-software interaction, and peripheral interfacing. Labs were primarily conducted using a Tiva C microcontroller and CCS.

---

# Labs

The lab series introduced core embedded systems concepts such as GPIO control, timers, interrupts, PWM, ADC input, and basic communication protocols. While this was a group-based lab course, the majority of the work—including implementation, debugging, and documentation—was independently completed by me due to limited contributions from assigned lab partners.

### Labs Included:
- **Lab 2 / Lab2Final** – Introduction to digital I/O: controlling onboard LEDs and push buttons using GPIO.
- **Lab 3** – Software debouncing for mechanical buttons and toggling LED states through interrupt-based control.
- **Lab 4** – Timer-based interrupt generation and system state transitions.
- **Lab 5** – PWM signal generation for LED brightness control using hardware timers.
- **Lab 6** – Analog-to-digital conversion (ADC) for sensor input, including potentiometer reading.
- **Lab 7** – ADC scaling and conversion to voltage or temperature readings for display or further processing.
- **Lab 8** – UART/serial communication basics and debugging over terminal.
- **Util Folder** – Contains reusable utilities and headers (GPIO configuration, macros, timing helpers, etc.).

---

## Final Project: Ultra Heat Sensor

**Title:** *Ultra Heat Sensor Alarm System*  
**Description:**  
This project combined multiple embedded subsystems into a working heat and distance alert mechanism. The system used:
- An ultrasonic sensor to detect distance
- A temperature sensor to monitor ambient heat
- A seven-segment display and LEDs for output
- A buzzer driven by PWM for alarm signaling

The project was designed to simulate a safety alert device, with adjustable thresholds and real-time response logic coded in C and ARM. I handled the complete integration, hardware testing, and software debugging.

---

## Concepts Covered

- GPIO configuration and edge-triggered interrupts  
- Hardware timer initialization and control  
- PWM signal generation and duty cycle adjustment  
- ADC sampling and signal conversion  
- UART communication and serial monitoring  
- Modular embedded C and ARM assembly programming  
- Real-time debugging and hardware troubleshooting

---

## Notes

All code in this repository was written with correctness, modularity, and documentation in mind. Due to unequal division of work in the lab group, I took the lead on nearly every lab and the final project, completing most assignments independently to ensure functionality and timely submission.

---

## Tools & Hardware

- **Platform:** Texas Instruments Tiva C ARM® Cortex  
- **IDE:** Code Composer Studio  
- **Languages:** C, ARM assembly 

---

## Contact

For questions or walkthroughs of any project or lab, feel free to connect with me on [LinkedIn](www.linkedin.com/in/akbar-aman-94b1b6263) or reach out directly.
