//
// Created by Stéphane on 27.10.23.
//

#include <assert.h>
#include "chip8screen.h"

static void chip8_screen_check_bounds(int x, int y) {
    assert(x >= 0 && x < CHIP8_WIDTH && y >= 0 && y < CHIP8_HEIGHT);
}

void chip8_screen_set(struct chip8_screen* screen, int x, int y) {
    chip8_screen_check_bounds(x, y);
    screen->pixels[y][x] = true;
}
bool chip8_screen_is_set(struct chip8_screen* screen, int x, int y) {
    chip8_screen_check_bounds(x, y);
    return screen->pixels[y][x];
}
