//
// Created by avina on 08-08-2025.
//

#ifndef EMU6502_H
#define EMU6502_H
#include <cstdint>
#include "bus.h"
class Bus;

class Emu6502 {
public:
    Emu6502();
    ~Emu6502();

    void connectBus(Bus* bus) {
        this->bus = bus;
    }

    enum FLAGS6502 {
        C = (1 << 0), // Carry bit
        Z = (1 << 1), // Zero
        I = (1 << 2), // Disable Interrupts
        D = (1 << 3), // Decimal Mode (unused)
        B = (1 << 4), // Break
        U = (1 << 5), // Unused
        V = (1 << 6), // Overflow
        N = (1 << 7), // Negative
    };

    uint8_t a = 0x00; // accumulator register
    uint8_t x = 0x00; // X register
    uint8_t y = 0x00; // Y register
    uint8_t stkp = 0x00; // Stack pointer (points to location on bus)


private:
    Bus* bus = nullptr; // forward declaration of Bus (see: https://en.wikipedia.org/wiki/Forward_declaration)

    [[nodiscard]] uint8_t read(uint16_t address) const; // nodiscard ensures return value cannot be ignored
    void write(uint16_t address, uint8_t data);
};



#endif //EMU6502_H
