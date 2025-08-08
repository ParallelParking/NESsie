//
// Created by avina on 08-08-2025.
//

#include "Bus.h"

Bus::Bus() {
    for (auto &i : ram) {
        i = 0x00; //Reset RAM
    }

    cpu.connectBus(this);
}

Bus::~Bus() = default;

void Bus::write(uint16_t address, uint8_t data) {
    if (address <= 0xFFFF) {
        ram[address] = data;
    }
}

uint8_t Bus::read(const uint16_t address, bool bReadOnly) const { // declaring const to guarantee no data modification
    if (address <= 0xFFFF) {
        return ram[address];
    }
    return 0x0000;
}


