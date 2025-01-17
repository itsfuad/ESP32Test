# ESP32 Diagonstic Project
## Overview

This project is designed to run diagnostic tests on an ESP32 microcontroller. It includes various tests to check the functionality of different components and peripherals of the ESP32.

## Features

- **System Information**: Displays CPU cores, revision, and frequency.
- **Memory Test**: Checks the available heap and PSRAM.
- **Flash Test**: Verifies the flash memory.
- **GPIO Test**: Tests the input and output functionality of GPIO pins.
- **ADC Test**: Reads values from an ADC pin.
- **WiFi Test**: Connects to a WiFi network and checks connectivity.
- **PSRAM Test**: Verifies the PSRAM functionality.
- **Timer Test**: Tests the timer functionality.

## Requirements

- ESP32 board
- Arduino IDE
- Required libraries:
    - Preferences
    - WiFi

## Installation

1. Install the Arduino IDE from [here](https://www.arduino.cc/en/software).
2. Install the required libraries via the Arduino Library Manager.
3. Clone this repository to your local machine.

## Usage

1. Open the `dig.ino` file in the Arduino IDE.
2. Select the appropriate board and port from the Tools menu.
3. Upload the sketch to the ESP32 board.
4. Open the Serial Monitor to view the diagnostic results.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## Contact

For any questions or inquiries, please contact the project maintainer.
