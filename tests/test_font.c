/* Test HELLO WORLD using si_sdl.c functions
To compile

gcc -g -O2 -Wall -Wextra -I./include \
  -o test_font \
  tests/test_font.c src/si_sdl.c src/si_font.c \
  $(pkg-config --cflags --libs sdl2)

./test_font
*/

#include <SDL2/SDL.h>
#include "../include/game.h"
#include "../include/si_sdl.h"

int main(int argc, char *argv[])
{
    SDL_Event events;
    int ret = 1;
    int running;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error : %s\n", SDL_GetError());
        goto err;
    }

    /*Create Game instance -- Create window*/
    Game g;
    g.window_width  = 800;
    g.window_height = 600;
    g.pixel_size    = 4;
    g.play_game     = 1;
    g.si            = NULL;

    g.win = SDL_CreateWindow(
        "Test Font", // Window Title
        60, 60,
        g.window_width,
        g.window_height,
        SDL_WINDOW_SHOWN
    );

    if (g.win == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"error : %s\n", SDL_GetError());
        goto sdl_quit;
    }

    /*Create renderer */
    g.ren = SDL_CreateRenderer(g.win, -1, SDL_RENDERER_ACCELERATED);
    if (g.ren == NULL)
    {
        SDL_Log("SDL_CreateRenderer error: %s\n", SDL_GetError());
        goto destroy_window;
    }

    SDL_SetRenderDrawColor(g.ren, 0, 0, 0, 255);
    SDL_RenderClear(g.ren);

    /*Draw text using si_sdl functions */
    int col0  = 4;
    int line0 = 2;

    si_text_display(&g, "ABCDEFGHIJKLM", line0 + 0, col0);
    si_text_display(&g, "NOPQRSTUVWXYZ", line0 + 1, col0);
    si_text_display(&g, "0123456789",   line0 + 2, col0);
    si_text_display(&g, "<>-*?=",       line0 + 3, col0 + 3);
    si_text_display(&g, "SPACE INVADERS", line0 + 5, col0);
    si_text_display(&g, "HELLO WORLD",    line0 + 6, col0);
    si_text_display(&g, "TEST FONTS",     line0 + 7, col0);

    SDL_RenderPresent(g.ren);


    /*Loop to keep window open */
    running = 1;
    while (running)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (events.key.keysym.sym == SDLK_q)
                        running = 0;
                    break;
            }
        }
    }

    ret = 0;

    SDL_DestroyRenderer(g.ren);
destroy_window:
    SDL_DestroyWindow(g.win);
sdl_quit:
    SDL_Quit();
err:
    return ret;
}
