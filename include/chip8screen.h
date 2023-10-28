//
// Created by Stéphane on 27.10.23.
//

#ifndef EMUCHIP8_CHIP8SCREEN_H
#define EMUCHIP8_CHIP8SCREEN_H

#include <stdbool.h>
#include "config.h"

struct chip8_screen {
    bool pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
};

void chip8_screen_set(struct chip8_screen* screen, int x, int y);
bool chip8_screen_is_set(struct chip8_screen* screen, int x, int y);
bool chip8_screen_draw_sprite(struct chip8_screen* screen, int x, int y, const char* sprite, int num);

#endif //EMUCHIP8_CHIP8SCREEN_H
