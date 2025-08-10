//
// Created by avina on 08-08-2025.
//

#ifndef EMU6502_H
#define EMU6502_H
#include <cstdint>
#include <string>
#include <vector>

class Bus;

class Emu6502 {
public:
    Emu6502();
    ~Emu6502();

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
    uint16_t pc = 0x0000; // Program Counter
    uint8_t status = 0x00; // Status register

    void connectBus(Bus* bus) {
        this->bus = bus;
    }

    // Addressing modes (see datasheet: https://www.princeton.edu/~mae412/HANDOUTS/Datasheets/6502.pdf):
    uint8_t IMP(); // Implied
    uint8_t IMM(); // Immediate
    uint8_t ZP0(); // Zero page
    uint8_t ZPX(); // Zero page indexed (ZPG, X)
    uint8_t ZPY(); // Zero page indexed (ZPG, Y)
    uint8_t REL(); // Relative
    uint8_t ABS(); // Absolute
    uint8_t ABX(); // Absolute indexed (ABS, X)
    uint8_t ABY(); // Absolute indexed (ABS, Y)
    uint8_t IND(); // Indirect
    uint8_t IZX(); // Indirect X
    uint8_t IZY(); // Indirect Y
    // uint8_t ACM(); // Accumulator

    // Opcodes (see datasheet above):
    uint8_t ADC(); // Add mem. to accumulator with carry
    uint8_t AND(); // AND mem. w accumulator
    uint8_t ASL(); // Shift one bit left
    uint8_t BCC(); // Branch on carry clear
    uint8_t BCS(); // Branch on carry set
    uint8_t BEQ(); // Branch on result zero
    uint8_t BIT(); // Test mem. bits with accumulator
    uint8_t BMI(); // Branch on result minus
    uint8_t BNE(); // Branch on result not zero
    uint8_t BPL(); // Branch on result plus
    uint8_t BRK(); // Force break
    uint8_t BVC(); // Branch on overflow clear
    uint8_t BVS(); // Branch on overflow set
    uint8_t CLC(); // Clear carry flag
    uint8_t CLD(); // Clear decimal mode
    uint8_t CLI(); // Clear interrupt disable bit
    uint8_t CLV(); // Clear overflow flag
    uint8_t CMP(); // Compare mem. and accumulator
    uint8_t CPX(); // Compare mem. and index X
    uint8_t CPY(); // Compare mem. and index Y
    uint8_t DEC(); // Decrement by 1
    uint8_t DEX(); // Decrement index X by 1
    uint8_t DEY(); // Decrement index Y by 1
    uint8_t EOR(); // XOR mem. with accumulator
    uint8_t INC(); // Increment by 1
    uint8_t INX(); // Increment index X by 1
    uint8_t INY(); // Increment index Y by 1
    uint8_t JMP(); // Jump to new location
    uint8_t JSR(); // Jump to new location, save return address
    uint8_t LDA(); // Load accumulator with mem.
    uint8_t LDX(); // Load index X with mem.
    uint8_t LDY(); // Load index Y with mem.
    uint8_t LSR(); // Shift 1 bit right
    uint8_t NOP(); // No operation
    uint8_t ORA(); // OR mem. with accumulator
    uint8_t PHA(); // Push accumulator on stack
    uint8_t PHP(); // Push processor status on stack
    uint8_t PLA(); // Pull accumulator from stack
    uint8_t PLP(); // Pull processor status from stack
    uint8_t ROL(); // Rotate 1 bit left
    uint8_t ROR(); // Rotate 1 bit right
    uint8_t RTI(); // Return from interrupt
    uint8_t RTS(); // Return from subroutine
    uint8_t SBC(); // Subtract mem. from accumulator with borrow
    uint8_t SEC(); // Set carry flag
    uint8_t SED(); // Set decimal mode
    uint8_t SEI(); // Set interrupt disable bit
    uint8_t STA(); // Store accumulator in memory
    uint8_t STX(); // Store index X in mem.
    uint8_t STY(); // Store index Y in mem.
    uint8_t TAX(); // Transfer accumulator to index X
    uint8_t TAY(); // Transfer accumulator to index Y
    uint8_t TSX(); // Transfer stack pointer to index X
    uint8_t TXA(); // Transfer index X to accumulator
    uint8_t TXS(); // Transfer index X to stack pointer
    uint8_t TYA(); // Transfer index Y to accumulator

    uint8_t XXX(); // Illegal opcode catchment

    void clock();
    void reset();
    void irq(); // Interrupt request handler
    void nmi(); // Non-maskable interrupt

    uint8_t fetch();
    uint8_t fetched = 0x00;

    uint16_t absoluteAddress = 0x0000;
    uint8_t relativeAddress = 0x00; // Branching has a range limit on 6502
    uint8_t opcode = 0x00;
    uint8_t cycles = 0;
private:
    Bus* bus = nullptr; // forward declaration of Bus (see: https://en.wikipedia.org/wiki/Forward_declaration)

    [[nodiscard]] uint8_t read(uint16_t address) const; // nodiscard ensures return value cannot be ignored
    void write(uint16_t address, uint8_t data);

    [[nodiscard]] uint8_t getFlag(FLAGS6502 flag) const;
    void setFlag(FLAGS6502 flag, bool v);

    struct INSTRUCTION {
        std::string name;
        uint8_t (Emu6502::*operate)() = nullptr; // function pointer to opcodes
        uint8_t (Emu6502::*addressingMode)() = nullptr; // function pointer to addressing mode
        uint8_t cycles = 0;
    };

    std::vector<INSTRUCTION> lookup;
};



#endif //EMU6502_H
