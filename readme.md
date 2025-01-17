# ESP32 Pin Testing Project

This project is designed to test various hardware functionalities of the ESP32 development board.

## Features Tested

- GPIO Output Testing
- ADC (Analog-to-Digital Converter) Testing
- WiFi Connectivity Testing
- FreeRTOS Task Scheduler Testing
- CPU Temperature Monitoring

## Hardware Requirements

- ESP32 Development Board
- USB Cable
- Computer with Arduino IDE

## Setup Instructions

1. Clone this repository
2. Open `Pintest.ino` in Arduino IDE
3. Connect your ESP32 board
4. Upload the code
5. Open Serial Monitor at 115200 baud rate

## Test Process

The program runs a series of self-tests automatically on startup:
1. Tests GPIO functionality
2. Tests ADC readings
3. Verifies WiFi initialization
4. Checks RTOS task creation
5. Monitors CPU temperature for 10 seconds

## Configuration

The project uses standard ESP32 configurations including:
- ADC with 12-bit resolution
- 80MHz Flash frequency
- Serial communication at 115200 baud
