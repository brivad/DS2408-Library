#include "DS2408.h"

DS2408 ds2408(4);           // Initialize DS2408 on pin 4
uint8_t lastInputState = 0; // Variable to store the last state of the input pins

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting DS2408 Input-Output Sync Example...");
    ds2408.begin(); // Initialize the DS2408 device
}

void loop()
{
    uint8_t currentInputState = ds2408.readDevice(); // Read all pin states at once

    // Mask out output pins (we assume inputs are in the lower 4 bits)
    currentInputState &= 0x0F; // Assuming inputs are on pins 0 to 3

    // Compare current input state with the last stored state
    if (currentInputState != lastInputState)
    {
        for (int pin = 0; pin < 4; pin++)
        {
            bool newState = currentInputState & (1 << pin); // Get the state of the current input pin
            bool oldState = lastInputState & (1 << pin);    // Get the state of the last input pin

            if (newState != oldState)
            { // Check if the state has changed
                // Log the state change
                Serial.print("Input pin ");
                Serial.print(pin);
                Serial.print(" changed to ");
                Serial.println(newState ? "HIGH" : "LOW");

                // Set the corresponding output pin to the new state (assuming output pins are 4 to 7)
                ds2408.writePin(pin + 4, newState); // Sync the output state to the input state
            }
        }

        // Update the last input state
        lastInputState = currentInputState;
    }

    delay(100); // Small delay to reduce CPU load and debounce inputs
}
