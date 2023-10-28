//
// Created by Stéphane on 27.10.23.
//

#include "chip8.h"
#include <memory.h>

const char chip8_default_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xf0, 0x10, 0xf0, 0x80, 0xf0,
    0xf0, 0x10, 0xf0, 0x10, 0xf0,
    0x90, 0x90, 0xf0, 0x10, 0x10,
    0xf0, 0x80, 0xf0, 0x10, 0xf0,
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    0xf0, 0x10, 0x20, 0x40, 0x40,
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    0xf0, 0x80, 0xf0, 0x80, 0xf0,
    0xf0, 0x80, 0xf0, 0x80, 0x80
};

void chip8_init(struct chip8* chip8) {
    memset(chip8, 0, sizeof(struct chip8));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}

void chip8_load(struct chip8* chip8, const char* buf, size_t size) {
    assert(size + CHIP8_PROGRAM_LOAD_ADRESS < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADRESS;
}

static void chip8_exec_extended(struct chip8* chip8, unsigned  short opcode) {
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    switch (opcode & 0xf000) {
        case 0x1000:
            // JP addr, 1nnn Jump to location nnn's
            chip8->registers.PC = nnn;
            break;
        case 0x2000:
            // CALL addr, 2nnn Call at location nnn
            chip8_stack_push(chip8, chip8->registers.PC);
            chip8->registers.PC = nnn;
            break;
        case 0x3000:
            // SE Vx, byte - 3xkk Skip next instruction if Vx=kk
            if (chip8->registers.V[x] == kk) {
                chip8->registers.PC += 2;
            }
            break;
    }
}

void chip8_exec(struct chip8* chip8, unsigned  short opcode) {
    switch (opcode) {
        case 0x00E0:
            // CLS: clear the display
            chip8_screen_clear(&chip8->screen);
            break;
        case 0x00EE:
            // Ret: Return from subroutine
            chip8->registers.PC = chip8_stack_pop(chip8);
            break;
        default:
            chip8_exec_extended(chip8, opcode);
    }
}