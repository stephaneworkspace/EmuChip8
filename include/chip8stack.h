//
// Created by Stéphane on 27.10.23.
//

#ifndef EMUCHIP8_CHIP8STACK_H
#define EMUCHIP8_CHIP8STACK_H

#include "config.h"

struct chip8;
struct chip8_stack {
    unsigned short stack[CHIP8_TOTAL_STACK_DEPTH];
};

void chip8_stack_push(struct chip8* chip8, unsigned short val);
unsigned short chip8_stack_pop(struct chip8* chip8);

#endif //EMUCHIP8_CHIP8STACK_H
