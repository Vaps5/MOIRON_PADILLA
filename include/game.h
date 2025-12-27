
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
  
  Uint64 ufo_last_move;
  Uint64 ufo_spawn_time;
  
  char update;


  int num_wave;       // numéro de la vague actuelle
  double enemy_speed; // vitesse des invaders
  double shot_speed;  // vitesse des tirs ennemis

  // UFO
  
  int ufo_active;        // 1 = UFO présent, 0 = pas d'UFO
  int ufo_x;             
  int ufo_y;             
  int ufo_direction;     // cf. Invaders
  float ufo_speed;       // Vitesse de déplacement
  int ufo_points;        // Points si détruit
  
} Game;

Game *game_new(void);
void game_run(Game *g);
void game_del(Game *g);

#endif
