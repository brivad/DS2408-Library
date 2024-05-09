
#include "DS2408.h"

DS2408 ds2408(4); // Initialize DS2408 on pin 4

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting DS2408 Example...");
    ds2408.begin(); // Initialize the DS2408 device
}

void loop()
{
    // assuming 4 to 7 are the output pins
    // when a number is sent over the serial monitor, the corresponding pin is toggled
    if (Serial.available())
    {
        int pin = Serial.parseInt();
        if (pin >= 4 && pin <= 7)
        {
            bool currentState = ds2408.readPin(pin);
            ds2408.writePin(pin, !currentState);
            Serial.print("Toggled pin ");
            Serial.print(pin);
            Serial.println(!currentState ? " LOW" : " HIGH");
        }
    }
    delay(1000);
}
