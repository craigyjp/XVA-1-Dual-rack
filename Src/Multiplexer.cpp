#include <Wire.h>
#include "Multiplexer.h"

void Multiplexer::selectChannel(uint8_t i2c_bus) {
    if (i2c_bus > 8) return;
    Wire.beginTransmission(address);
    Wire.write(1 << i2c_bus);
    Wire.endTransmission();
}

Multiplexer::Multiplexer(uint8_t address) : address(address) {}
