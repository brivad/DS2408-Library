# DS2408 Library

This library provides an interface for controlling the DS2408 1-Wire digital I/O chip using the Arduino platform.

## Installation

- Download this repository.
- In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library and select the downloaded ZIP.
- Ensure you have the OneWire library installed. It can be installed via the Library Manager in Arduino IDE. Search for "OneWire" by Paul Stoffregen, and install version 2.3.8 or later.

## Usage

See the included example in the `examples` folder for how to use the library.

## API

- `begin()`: Initialize the DS2408 device.
- `readPin(uint8_t pin)`: Read the state of a specific pin.
- `writePin(uint8_t pin, bool state)`: Write a state to a specific pin.
- `readDevice()`: Read the states of all pins.

## License

This library is released under the MIT license.
