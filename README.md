# Smart Aquarium System

## Overview
The **Smart Aquarium System** is an IoT-based solution designed to automate and monitor the conditions of an aquarium environment. It incorporates features such as water quality monitoring, temperature control, water level detection, turbidity analysis, and automatic feeding. This system is built using Arduino Uno, and the simulation is developed using **Proteus**.

## Features
- **pH Monitoring**: Continuously monitors the pH level of the water to ensure a healthy aquatic environment.
- **Water Level Detection**: Alerts when the water level is too low or too high.
- **Turbidity Sensor**: Monitors water clarity.
- **Temperature Sensor**: Keeps track of water temperature with a waterproof sensor.
- **Automatic Feeding**: Dispenses food for the fish at regular intervals.
- **Display Interface**: Displays system metrics such as pH, temperature, and turbidity on an LCD.

## Hardware Components
- Arduino Uno
- pH Sensor Module
- Turbidity Sensor Module
- Waterproof DS18B20 Temperature Sensor
- Water Level Sensor
- LCD Display
- Servo Motor (for automatic feeding)
- Resistors, capacitors, and other electrical components

## Software Components
- **Arduino IDE**: For programming the Arduino Uno.
- **Proteus**: For circuit simulation and testing.

## How It Works
- The Arduino reads data from the sensors (pH, turbidity, temperature, water level).
- It processes the data and displays the results on the LCD screen.
- The servo motor feeds the fish automatically at pre-defined intervals.
- The system provides visual or audible alerts if any parameter is outside the desired range.
