Repository Overview

This repository contains a Renesas RA microcontroller project named StepperMotorController. It is configured with the Renesas Flexible Software Package (FSP) and uses ThreadX as the RTOS.

Main Directory Layout
StepperMotorController/

src/ – application‐level C++ files (motor control logic, thread entries, drivers).

ra_gen/ – auto‑generated source from FSP (initializes threads, peripherals, vectors).

ra_cfg/ – FSP configuration headers.

ra/ – vendor libraries (CMSIS, ThreadX, etc.).

script/fsp.ld – linker script.

configuration.xml & ra_cfg.txt – project configuration.

Threads and Entry Points
The generated code creates three threads (ThreadX):

thread0_main – starts automatically and resumes the other threads. Its entry function enables the motor driver and resumes thread1_motor_drive and thread2_monitor after short delays.

thread1_motor_drive – handles stepper motor operation. It initializes peripherals (SDADC, timers, DAC), runs a calibration routine, then continuously reads an ADC value and drives the motor according to the measurement, including acceleration control and range checks.

thread2_monitor – periodically performs ADC readings of various voltages and currents.

Thread creation and startup are generated in ra_gen/thread0_main.c and ra_gen/thread1_motor_drive.c (see tx_thread_create calls).

Motor Control Logic
Custom motor control resides in motor_control.cpp. Functions here adjust PWM duty cycle and frequency, handle full-step or half-step sequences, implement spinCW/spinCCW, detect end limits, and perform calibration. For example, the clockwise spin sequence iterates through step patterns while delaying between steps.

Hardware Driver Utilities
controller_driver.cpp wraps low-level peripheral interactions:

Initializes SDADC and timers.

Reads a 24‑bit ADC and converts it to millivolts.

Controls a DAC to set an amplifier reference voltage.

A typical ADC read sequence waits for completion, then converts the result using gain factors.

Configuration and Constants
Header appDefines.h defines pin macros, ADC constants, and timing parameters used throughout the code (e.g., MOTOR_STEP_DELAY, PCLKD_CLOCK).
