#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8.h"

int main(int argc, char *argv[]) {

    struct chip8 chip8;
    chip8_memory_set(&chip8.memory, 0x400, 'Z');
    printf("%c\n", chip8_memory_get(&chip8.memory, 0x400));

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
            if(e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 40;
        r.h = 40;
        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer); // Ajout de la destruction du rendu
    SDL_DestroyWindow(window);
    SDL_Quit(); // Assurez-vous de quitter SDL proprement
    return 0;
}
