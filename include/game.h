
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

  /*
  // F4

  int num_wave;       // numéro de la vague actuelle
  double enemy_speed; // vitesse des invaders
  double shot_speed;  // vitesse des tirs ennemis
  */
  
} Game;

Game *game_new(void);
void game_run(Game *g);
void game_del(Game *g);

#endif
