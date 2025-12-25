/*
To compile

gcc -g -O2 -Wall -Wextra -o si src/*.c $(pkg-config --cflags --libs sdl2)
./si
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/game.h"
#include "../include/si_sdl.h"
#include "../include/si_menu.h"
#include "../include/si.h"

#define CHAR_W_UNITS 6
#define CHAR_H_UNITS 9
#define NB_COLS 26
#define NB_LINES 30

#define TANK_W_PIXELS 13
#define TANK_H_PIXELS 8


static int tank_y_px(const Game *g)
{
  return (NB_LINES - 1) * CHAR_H_UNITS * g->pixel_size;
}

static int clamp_tank_x(const Game *g, int x)
{
  int tank_w = TANK_W_PIXELS * g->pixel_size;
  if (x < 0) return 0;
  if (x > g->window_width - tank_w) return g->window_width - tank_w;
  return x;
}

static void tank_try_fire(Game *g)
{
  Tank *t = &g->si->tank;
  if (t->destroyed) return;
  if (t->firing) return;

  int px = g->pixel_size;
  int tank_w = TANK_W_PIXELS * px;

  t->firing  = 1;
  t->shoot_x = t->x + tank_w / 2;
  t->shoot_y = tank_y_px(g) - TANK_H_PIXELS * px;
}

static void matrix_reset(void)
{
  char *m = si_get_matrix();
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 11; ++j) {
      if (i == 0) m[i * 11 + j] = 1;
      else if (i == 1 || i == 2) m[i * 11 + j] = 2;
      else m[i * 11 + j] = 3;
    }
  }
}


/* F4
  
  // Affichage du numéro de vague
  
  char wave[15];
  snprintf(wave, sizeof(wave), "WAVE: %d", g->current_wave);
  si_text_display(g, wave, 1, 10); // à changer si besoin (voir apres les tests)
  
  // Affichage du meilleur score
  
  char high_score[50];
  snprintf(high_score, sizeof(high_score), "HIGH: %d", g->si->score_highest);
  si_text_display(g, high_score, 1, 18); // à changer si besoin (voir apres les tests)
  */

static void game_update(Game *g)
{
  SDL_SetRenderDrawColor(g->ren, 0x2b, 0x2a, 0x33, 0xff);
  SDL_RenderClear(g->ren);

  if (!g->play_game) {
    menu(g);
  } else if (g->si->life_1 == 0) {
    game_over(g);
  } else {
    si_text_display(g, "SCORE<1> HI-SCORE SCORE<2>", 0, 0);

    char s1[16], sh[16], s2[16];
    snprintf(s1, sizeof(s1), "%04d", g->si->score_1);
    snprintf(sh, sizeof(sh), "%04d", g->si->score_highest);
    snprintf(s2, sizeof(s2), "%04d", g->si->score_2);

    si_text_display(g, s1, 1, 1);
    si_text_display(g, sh, 1, 11);
    si_text_display(g, s2, 1, 21);

    si_invaders_display(g, g->si->invaders.x, g->si->invaders.y);

    if (g->si->invaders.firing) {
      si_invader_shoot_display(g, g->si->invaders.bomb_x, g->si->invaders.bomb_y);
    }

    int ty = tank_y_px(g);
    if (g->si->tank.destroyed) {
      int type = (g->si->tank.destroyed_count / 6) % 2;
      si_tank_explode_display(g, type, g->si->tank.x, ty);
    } else {
      si_tank_display(g, g->si->tank.x, ty);
    }

    if (g->si->tank.firing) {
      si_tank_shoot_display(g, g->si->tank.shoot_x, g->si->tank.shoot_y);
    }

    char lives[32];
    snprintf(lives, sizeof(lives), "LIVES %d", g->si->life_1);
    si_text_display(g, lives, NB_LINES - 1, 0);
  }

  SDL_RenderPresent(g->ren);
  g->update = 0;
}



Game *game_new(void)
{
  Game *g = malloc(sizeof(*g));
  if (!g) return NULL;

  g->win = NULL;
  g->ren = NULL;
  g->si  = NULL;

  g->pixel_size = 2;

  g->window_width  = NB_COLS  * CHAR_W_UNITS * g->pixel_size;
  g->window_height = NB_LINES * CHAR_H_UNITS * g->pixel_size;

  g->play_game = 0;
  g->update = 1;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    free(g);
    return NULL;
  }

  g->win = SDL_CreateWindow(
      "Space Invaders",
      SDL_WINDOWPOS_CENTERED, 0,
      g->window_width, g->window_height,
      SDL_WINDOW_BORDERLESS
  );
  if (!g->win) {
    SDL_Quit();
    free(g);
    return NULL;
  }

  g->ren = SDL_CreateRenderer(g->win, -1, SDL_RENDERER_ACCELERATED);
  if (!g->ren) {
    SDL_DestroyWindow(g->win);
    SDL_Quit();
    free(g);
    return NULL;
  }

  g->si = si_new(g->window_width, g->window_height, g->pixel_size);
  if (!g->si) {
    SDL_DestroyRenderer(g->ren);
    SDL_DestroyWindow(g->win);
    SDL_Quit();
    free(g);
    return NULL;
  }

  si_tank_set_position(g);

  g->si->invaders.x = 0;
  g->si->invaders.y = 2 * CHAR_H_UNITS * g->pixel_size;
  g->si->invaders.direction = 1;
  g->si->invaders.firing = 0;

  g->freq = SDL_GetPerformanceFrequency();
  g->count_invaders = SDL_GetPerformanceCounter();
  g->count_shoot    = SDL_GetPerformanceCounter();

  srand((unsigned)time(NULL));

  return g;
}

void game_del(Game *g)
{
  if (!g) return;

  if (g->si) si_del(g->si);

  if (g->ren) SDL_DestroyRenderer(g->ren);
  if (g->win) SDL_DestroyWindow(g->win);

  SDL_Quit();
  free(g);
}

void game_run(Game *g)
{
  int running = 1;
  float inv_period = 0.1f;
  float shoot_period = 0.005f;

  while (running) {
    SDL_Event events;
    Uint64 c_shoot;
    Uint64 c_invaders;

    while (SDL_PollEvent(&events)) {
      switch (events.type) {

      case SDL_QUIT:
        running = 0;
        break;

      case SDL_KEYDOWN:
        switch (events.key.keysym.sym) {
        case SDLK_q:
        case SDLK_ESCAPE:
          running = 0;
          break;

        case SDLK_SPACE:
          if (g->play_game) {
            tank_try_fire(g);
            g->update = 1;
          } else {
            g->play_game = 1;
            g->update = 1;
          }
          break;

        default:
          if (g->si->life_1 == 0) running = 0;
          break;
        }
        break;

      case SDL_MOUSEMOTION:
        if (g->play_game) {
          g->si->tank.x = clamp_tank_x(g, events.motion.x);
          g->update = 1;
        }
        break;

      default:
        break;
      }
    }

    if (g->play_game == 0) {
      g->update = 1;
    } else {
      c_invaders = SDL_GetPerformanceCounter();
      c_shoot    = SDL_GetPerformanceCounter();

      if ((float)(c_invaders - g->count_invaders) / g->freq > inv_period) {
        if (g->si->tank.destroyed) {
          g->si->tank.destroyed_count++;
          if (g->si->tank.destroyed_count > 20) {
            g->si->tank.destroyed = 0;
            g->si->tank.destroyed_count = 0;
            si_tank_set_position(g);
          }
          g->update = 1;
        } else {
          if (g->si->invaders.direction == 1) {
            if (!si_invaders_can_move_right(g->si))
              g->si->invaders.direction = -1;
            else
              g->update = 1;
          } else {
            if (!si_invaders_can_move_left(g->si))
              g->si->invaders.direction = 1;
            else
              g->update = 1;
          }
        }
        g->count_invaders = c_invaders;
      }

      if ((float)(c_shoot - g->count_shoot) / g->freq > shoot_period) {
        if (g->si->tank.firing) {
          if (si_tank_shoot_can_move_up(g->si))
            g->update = 1;

          if (si_invader_is_hit(g->si)) {
            if (g->si->score_1 > g->si->score_highest)
              g->si->score_highest = g->si->score_1;
            g->update = 1;
          }
        }

        if (!g->si->invaders.firing) {
          si_invaders_get_column(g->si);
          g->si->invaders.firing = 1;
        }

        if (g->si->invaders.firing) {
          if (si_invaders_bomb_can_move_down(g->si))
            g->update = 1;

          if (si_tank_is_hit(g->si))
            g->update = 1;
        }

        g->count_shoot = c_shoot;
      }

      if (si_matrix_count() == 0) {
        matrix_reset();
        inv_period *= 0.9f;
        shoot_period *= 0.9f;
        g->update = 1;
      }
    }

    if (g->update)
      game_update(g);
  }
}