
#ifndef DS2408_H
#define DS2408_H

#include <OneWire.h>

class DS2408
{
public:
    explicit DS2408(uint8_t pin);
    void begin();
    bool readPin(uint8_t pin);
    void writePin(uint8_t pin, bool state);
    void printDeviceAddress();
    uint8_t readDevice();

private:
    OneWire net;
    byte addr[8];
    bool deviceFound;
    void writeDevice(uint8_t state);
};

#endif
