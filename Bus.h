//
// Created by avina on 08-08-2025.
//

#ifndef BUS_H
#define BUS_H

#include <array>
#include <cstdint>

#include "Emu6502.h"

class Bus {
public:
    Bus();
    ~Bus(); // ~ signifies destructor.

    Emu6502 cpu;
    std::array<uint8_t, 64 * 1024> ram{}; // 64KB fake RAM

    // Bus Read/Write:
    void write(uint16_t address, uint8_t data);
    uint8_t read(uint16_t address, bool bReadOnly = false) const;
};



#endif //BUS_H
