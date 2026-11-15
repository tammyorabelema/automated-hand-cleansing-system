# Automated Hand-Cleansing Device

## Project overview

This completed undergraduate Biomedical Engineering project involved the design, construction, implementation, and functional testing of an automated hand-cleansing device at Bells University of Technology (July 2023). The assembled device performed its intended operating sequence: it detected hand placement, initiated mist production for the programmed interval, switched to blower-assisted hand drying, and completed the cycle with the programmed timing and LCD status messages.

The device also incorporated ultrasonic liquid-level monitoring and an audible low-level alert. The project report documents the design, hardware implementation, construction, and functional tests.

## Main system components

- Arduino Nano microcontroller
- Infrared hand-detection sensors
- Ultrasonic mist makers
- Ultrasonic liquid-level sensor
- DC blower fans
- LCD interface
- MOSFET switching circuitry
- Buzzer and mute switch
- Fibreglass device enclosure and liquid reservoir

## Operating sequence

1. The infrared sensors detect hand placement in the device.
2. The controller checks the liquid-level condition.
3. The misting system operates for the programmed interval.
4. Misting stops and the blower fans begin the drying stage.
5. The fans stop at the end of the programmed cycle.
6. The LCD indicates completion and the device returns to standby.

## Functional testing

The completed device was tested for its intended functions, including hand detection, liquid-level sensing, mist production, fan operation, and the timed misting-to-drying sequence. The project is presented here as a completed engineering build.

## Scope of this repository

This repository documents the engineering design and implementation of the device. 

## Software

The Arduino source is available at `software/Arduino/humidifier_Hand.ino`. Personal identifying text has been removed from the LCD startup display, and the on-screen wording has been changed from “Sanitizing Hands” to “Misting Hands”. These are display-text edits; the control sequence and programmed timing have not intentionally been changed.

## Safety note

The original academic report describes an isopropyl-alcohol liquid mixture used with an ultrasonic mist maker. This repository records the completed academic project; it is not an instruction to reproduce or operate that fluid configuration. Aerosolising flammable liquids can create fire and inhalation hazards, so any practical recreation or adaptation requires an appropriate safety assessment and a compatible fluid-delivery design.

## Project details

- **Discipline:** Biomedical Engineering
- **Institution:** Bells University of Technology
- **Completion:** July 2023
