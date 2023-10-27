//
// Created by Stéphane on 25.10.23.
//

#ifndef EMUCHIP8_CHIP8_H
#define EMUCHIP8_CHIP8_H

#include "config.h"
#include "chip8memory.h"
#include "chip8registers.h"
#include "chip8stack.h"
#include "chip8keyboard.h"

struct chip8 {
    struct chip8_memory memory;
    struct chip8_stack stack;
    struct chip8_registers registers;
    struct chip8_keyboard keyboard;
};

#endif //EMUCHIP8_CHIP8_H
