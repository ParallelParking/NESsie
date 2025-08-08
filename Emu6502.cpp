//
// Created by avina on 08-08-2025.
//

#include "Emu6502.h"

Emu6502::Emu6502() = default;

Emu6502::~Emu6502() = default;

uint8_t Emu6502::read(uint16_t address) const {
    return bus->read(address, false);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Emu6502::write(uint16_t address, uint8_t data) {
    return bus->write(address, data);
}

uint8_t Emu6502::getFlag(const FLAGS6502 flag) const {
    return ((status & flag) > 0) ? 1 : 0;
}

void Emu6502::setFlag(const FLAGS6502 flag) {
    status |= flag;
}
