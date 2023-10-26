//
// Created by Stéphane on 26.10.23.
//

#ifndef EMUCHIP8_CHIP8REGISTERS_H
#define EMUCHIP8_CHIP8REGISTERS_H
#include "config.h"

struct chip8_registers {
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS];
    unsigned short I;
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short PC; // Program Counter
    unsigned short SP; // Stack Pointer
};

#endif //EMUCHIP8_CHIP8REGISTERS_H
