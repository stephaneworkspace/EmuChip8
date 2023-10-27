#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "chip8keyboard.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = { SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8,
                                              SDLK_9, SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argc, char *argv[]) {

    struct chip8 chip8;
    chip8_init(&chip8);

    chip8_screen_set(&chip8.screen, 10, 1);

    /*
     Register test
     =============
     chip8.registers.V[0x0f] = 50;
     chip8_memory_set(&chip8.memory, 0x400, 'Z');
     printf("%c\n", chip8_memory_get(&chip8.memory, 0x400));
    */
    /*
     Stack test
     =============
    chip8.registers.SP = 0;
    chip8_stack_push(&chip8, 0xff);
    chip8_stack_push(&chip8, 0xaa);
    printf("%x\n", chip8_stack_pop(&chip8));
    printf("%x\n", chip8_stack_pop(&chip8));
    */
    /*
     Keyboard test
     =============
    */
    //chip8_keyboard_down(&chip8.keyboard, 0x0f);
    //bool is_down = chip8_keyboard_is_down(&chip8.keyboard, 0x0f);
    //printf("%i\n", (int) is_down);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
            EMULATOR_WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CHIP8_WIDTH * CHIP8_WINDOWS_MULTIPLIER,
            CHIP8_HEIGHT * CHIP8_WINDOWS_MULTIPLIER,
            SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    int running = 1;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                {
                    running = 0;
                }
                break;
                case SDL_KEYDOWN:
                {
                    char key = e.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1)
                        chip8_keyboard_down(&chip8.keyboard, vkey);
                }
                break;
                case SDL_KEYUP:
                {
                    char key = e.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1)
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_WIDTH; x++) {
            for (int y = 0; y < CHIP8_HEIGHT; y++) {
                if (chip8_screen_is_set(&chip8.screen, x, y)) {
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOWS_MULTIPLIER;
                    r.y = y * CHIP8_WINDOWS_MULTIPLIER;
                    r.w = CHIP8_WINDOWS_MULTIPLIER;
                    r.h = CHIP8_WINDOWS_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer); // Ajout de la destruction du rendu
    SDL_DestroyWindow(window);
    SDL_Quit(); // Assurez-vous de quitter SDL proprement
    return 0;
}
