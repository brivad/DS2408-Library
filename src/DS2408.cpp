
#include "DS2408.h"
#include <Arduino.h>

DS2408::DS2408(uint8_t pin) : net(pin), deviceFound(false)
{
    memset(addr, 0, sizeof(addr));
}

void DS2408::begin()
{
    net.reset_search();
    deviceFound = false;

    while (net.search(addr))
    {
        if (OneWire::crc8(addr, 7) == addr[7] && addr[0] == 0x29)
        {
            deviceFound = true;
            Serial.print("Found DS2408 ");
            printDeviceAddress();
            break;
        }
    }

    if (!deviceFound)
    {
        Serial.println("No DS2408 found. Check wiring or device.");
    }
}

bool DS2408::readPin(uint8_t pin)
{
    if (!deviceFound)
    {
        Serial.println("Attempt to read from a non-existent device.");
        return false;
    }
    return readDevice() & (1 << pin);
}

void DS2408::writePin(uint8_t pin, bool state)
{
    if (!deviceFound)
    {
        Serial.println("Attempt to write to a non-existent device.");
        return;
    }
    uint8_t currentState = readDevice();
    uint8_t newState = state ? (currentState | (1 << pin)) : (currentState & ~(1 << pin));
    writeDevice(newState);
}

void DS2408::printDeviceAddress()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Serial.print(addr[i], HEX);
    }
    Serial.println();
}

uint8_t DS2408::readDevice()
{
    uint8_t buf[13];
    buf[0] = 0xF0; // Read PIO Registers command
    buf[1] = 0x88; // LSB of the address to read from
    buf[2] = 0x00; // MSB of the address to read from

    net.reset();
    net.select(addr);
    net.write_bytes(buf, 3);     // Send read command
    net.read_bytes(buf + 3, 10); // Read 10 bytes back, including data and CRC16

    if (!OneWire::check_crc16(buf, 11, &buf[11]))
    {
        Serial.println("CRC error in readDevice()");
        return 0; // Return zero as error state
    }
    return buf[3]; // Return the state of the pins
}

void DS2408::writeDevice(uint8_t state)
{
    uint8_t buf[13];
    buf[0] = 0x5A;   // Write PIO Registers command
    buf[1] = state;  // Data to write
    buf[2] = ~state; // Inverted byte for confirmation

    net.reset();
    net.select(addr);
    net.write_bytes(buf, 3);    // Send command and data bytes
    net.read_bytes(buf + 3, 1); // Read back confirmation byte

    if (buf[3] != 0xAA)
    {
        Serial.println("Failed to confirm write in writeDevice()");
    }
}
