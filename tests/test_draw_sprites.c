/*Test draw sprites without get si structure 
To compile

gcc -g -O2 -Wall -Wextra -I./include \
  -o test_draw_sprites \
  tests/test_draw_sprites.c src/si_sdl.c src/si_font.c \
  $(pkg-config --cflags --libs sdl2)

./test_draw_sprites
*/

#include <SDL.h>
#include "../include/game.h"
#include "../include/si_sdl.h"
#include "../include/si.h"
#include "../include/si_font.h"



int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    Game g;
    g.window_width  = 800;
    g.window_height = 600;
    g.pixel_size    = 3;
    g.play_game     = 1;
    g.si            = NULL;   /* aún no usamos Si aquí */

    g.win = SDL_CreateWindow(
        "Test draw sprites",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        g.window_width,
        g.window_height,
        SDL_WINDOW_SHOWN
    );
    if (!g.win) {
        SDL_Log("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    g.ren = SDL_CreateRenderer(g.win, -1, SDL_RENDERER_ACCELERATED);
    if (!g.ren) {
        SDL_Log("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(g.win);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(g.ren, 0, 0, 0, 255);
    SDL_RenderClear(g.ren);

    /* invaders  */
    si_invaders_display(&g, 80, 60);

    /* 2. Tank in middle */
    int width;
    si_font_tank_get(&width);
    int tank_w_px = width * g.pixel_size;
    int tank_x = (g.window_width - tank_w_px) / 2;
    int tank_y = g.window_height - 4 * g.pixel_size * 8;

    si_tank_display(&g, tank_x, tank_y);

    SDL_RenderPresent(g.ren);

    int running = 1;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(g.ren);
    SDL_DestroyWindow(g.win);
    SDL_Quit();
    return 0;
}
