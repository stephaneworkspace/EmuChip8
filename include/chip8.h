//
// Created by Stéphane on 25.10.23.
//

#ifndef EMUCHIP8_CHIP8_H
#define EMUCHIP8_CHIP8_H

#include "config.h"
#include "chip8memory.h"
#include "chip8registers.h"

struct chip8 {
    struct chip8_memory memory;
    struct  chip8_registers registers;
};

#endif //EMUCHIP8_CHIP8_H
