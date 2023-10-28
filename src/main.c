#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "chip8keyboard.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = { SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8,
                                              SDLK_9, SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("You must provide a file to load\n");
        return -1;
    }

    const char* filename = argv[1];
    printf("The filename to load is: %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Failed to open the file");
        return -1;
    }

    fseek(f, 0, SEEK_END); // go end file
    long size = ftell(f); // Position end file
    fseek(f, 0, SEEK_SET); // begin of file

    char buf[size];
    int res = fread(buf, size, 1, f);
    if (res != 1) {
        printf("Failed to read from file");
        return -1;
    }
    //printf("&s\n", buf);

    struct chip8 chip8;
    chip8_init(&chip8);
    chip8_load(&chip8, buf, size);

    //chip8_exec(&chip8, 0x1ff2);
    //printf("%x\n", chip8.registers.PC);

    // test ecriture et blank
    // chip8_screen_draw_sprite(&chip8.screen, 32, 30, &chip8.memory.memory[0x00], 5);
    // chip8_exec(&chip8, 0x00E0);

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
    // Drawing pixel screen
    //chip8_screen_set(&chip8.screen, 10, 1);
    //chip8.registers.sound_timer = 255;

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

        if (chip8.registers.delay_timer > 0) {
            usleep(100);
            chip8.registers.delay_timer -= 1;
        }
        if (chip8.registers.sound_timer > 0) {
            // Beep (Windows.h)
            // Beep(8000, 100 + chip8.registers.sound_timer);
            chip8.registers.sound_timer -= 1;
        }

        unsigned short opcode = chip8_memory_get_short(&chip8.memory, chip8.registers.PC);
        chip8.registers.PC += 2;
        chip8_exec(&chip8, opcode);
        printf("%x\n", opcode);
    }

    SDL_DestroyRenderer(renderer); // Ajout de la destruction du rendu
    SDL_DestroyWindow(window);
    SDL_Quit(); // Assurez-vous de quitter SDL proprement
    return 0;
}
