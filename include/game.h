
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "si.h"    

typedef struct
{
  SDL_Window *win;
  SDL_Renderer *ren;
  int window_width;
  int window_height;
  int pixel_size;
  int play_game;
  Si *si;
  Uint64 freq;
  Uint64 count_invaders;
  Uint64 count_shoot;
  char update;
} Game;

#endif
