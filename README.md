# Embedded Systems Projects — ECE 266

Repository owner: ak23bar  
Course: ECE 266 — Embedded Systems (educational / lab exercises)

Overview
--------
This repository is a collection of lab exercises, examples, and utilities used for teaching and learning embedded systems in ECE 266. It is intended to be an educational resource that demonstrates common embedded-software workflows, peripheral drivers, low-level C and assembly techniques, build scripts, and hardware notes for the target platforms used in the course.

Goals
-----
- Provide reproducible, well-documented lab examples that illustrate embedded concepts (GPIO, timers, interrupts, UART, ADC, PWM, state machines, etc.).
- Give students practical references for toolchain configuration, build and flash steps, and hardware setup.
- Preserve lab history and make it easy to archive or reuse projects in later courses.

Repository structure
--------------------
Top-level folders normally include one directory per lab and a `Util/` directory for shared utilities:

- Lab2, Lab3, Lab4, Lab5, Lab6, Lab7, Lab8, ...
- Lab2Final
- Util

Each lab folder typically contains:
- Source code (C, assembly)
- Board- or lab-specific README.md (hardware notes, required components, expected behavior)
- Build files (Makefile, project file for IDE/toolchain)
- Startup code and linker scripts when required

Refer to the README in each lab directory for lab-specific build and run instructions.

Getting started (prerequisites)
------------------------------
You will commonly need:
- A cross-toolchain for the target microcontroller (examples below)
- Basic familiarity with command-line builds (Makefile) and your IDE (if provided)
- Hardware: the microcontroller development board used in the lab (see lab README)

Typical toolchains and utilities
- GCC ARM Embedded (gcc-arm-none-eabi) for ARM Cortex-M devices
- TI Code Composer Studio (CCS) for TI microcontrollers (if the lab uses TI-specific devices)
- avr-gcc for AVR-based boards (if applicable)
- OpenOCD, J-Link, or vendor flashing utilities for programming the target board
- make, cmake, or the IDE project system used in a lab

How to build and run (general)
------------------------------
1. Open the lab folder you want to build (e.g., `Lab4/`).
2. Read the lab-specific README in that folder for hardware, pinouts, and any required external components.
3. Choose a supported toolchain and configure your environment (make sure the cross-compiler is on PATH).
4. Typical build (if a Makefile is provided):
   - make clean
   - make all
5. Flash the produced binary using the flashing tool appropriate for your board (OpenOCD, J-Link, vendor tools).
6. Use a serial terminal (e.g., `minicom`, `screen`, `PuTTY`) to observe UART output if available.
7. If using an IDE, open the project file and follow the IDE’s build/flash steps.

Hardware and pin mappings
-------------------------
Hardware details and pin mappings are lab-specific and appear in each lab’s README or top-of-source comments. Always confirm:
- Power and ground connections
- Clock and oscillator settings
- Peripheral pin assignments (GPIO, UART, I2C, SPI, ADC)
- Any required jumpers or external circuitry (LEDs, buttons, sensors)

Coding conventions and documentation
------------------------------------
- Prefer clear, commented code that explains why something is done (not only what).
- Keep functions small and single-purpose; use meaningful identifiers.
- Document assumptions about clock frequency, peripheral configuration, and interrupt priorities.
- Where applicable, include a short README inside the lab directory describing:
  - hardware used
  - build toolchain and version
  - exact build and flash commands
  - expected behavior and test steps
  - known limitations or TODOs

Testing and debugging tips
--------------------------
- Use the debugger to step through startup and interrupt code.
- Add serial or LED-based debug indicators if a debugger is not available.
- Keep a minimal “smoke test” program that toggles an LED to verify the board and toolchain work before running more complex code.
- For timing-sensitive labs, measure waveforms with an oscilloscope or logic analyzer.

Contributing
------------
Contributions are welcome — especially from students improving docs, fixing typos, or adding lab writeups. Suggested workflow:
1. Create a branch for your change: git checkout -b my-change
2. Make focused commits with descriptive messages
3. Add or update a README in the lab folder if you change hardware, build steps, or expected behavior
4. Open a pull request describing the changes

When adding a new lab or project:
- Include a short README describing required hardware, exact build steps, and expected behavior
- Prefer adding tests or a small verification script (e.g., how to confirm UART output)

Archiving or removing projects
------------------------------
To keep the main branch minimal while preserving history, consider:
- Moving completed/old projects to an `archive/` directory in the repo
- Creating an `archive/` branch and linking from the PR that removes the project
- Exporting and storing archived labs as ZIP releases and linking to them

Security and safety
-------------------
- This repository contains code intended to run on hardware. Test on development boards and not on production hardware.
- Be mindful when connecting external components (voltage levels, current limits). Follow board datasheets and lab instructor guidance.

Acknowledgements
----------------
This repository was created for educational use in ECE 266 and is maintained by ak23bar. Lab content may be based on course materials and lab assignments provided in the course.

Contact
-------
Repository owner: ak23bar  
For questions about the labs or to report issues, open a GitHub issue or contact the repository owner directly.

Changelog
---------
- 2025-11-19 — README revised and expanded to reflect ECE 266 educational use.
