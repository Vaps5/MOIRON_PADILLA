#include <stdio.h>
#include "../include/si_menu.h"
#include "../include/si_sdl.h"

void menu(Game *g)
{
  si_text_display(g, "SCORE<1> HI-SCORE SCORE<2>", 0, 0);
  si_text_display(g, "0000     0000     0000", 2, 2);
  si_text_display(g, "PLAY", 6, 11);
  si_text_display(g, "SPACE  INVADERS", 9, 6);
  si_text_display(g, "*SCORE ADVANCE TABLE*", 14, 3);
  
  int sprite_x = 12 * 6 * g->pixel_size; // positionnement à la 12eme colonne
  int ufo_x = 11 * 6 * g->pixel_size;

  si_invader_display(g, SI_TYPE_OCTOPUS, 0, sprite_x, 18 * 8 * g->pixel_size);
  si_text_display(g, "10 POINTS", 17, 8);
  
  si_invader_display(g, SI_TYPE_CRAB, 0, sprite_x, 21 * 8 * g->pixel_size);
  si_text_display(g, "20 POINTS", 20, 8);
  
  si_invader_display(g, SI_TYPE_SQUID, 0, sprite_x, 24 * 8 * g->pixel_size);
  si_text_display(g, "30 POINTS", 23, 8);

  si_ufo_display(g, ufo_x, 28 * 8 * g->pixel_size);
  si_text_display(g, "?? POINTS", 26, 8);
  
  si_text_display(g, "CREDIT", 29, 10);
}

void game_over(Game *g)
{
  si_text_display(g, "==========================", 6, 0);
  si_text_display(g, "GAME  OVER", 7, 8);
  si_text_display(g, "==========================", 8, 0);
  
  // Affichage du score final
    
  char final_score[50];
  snprintf(final_score, sizeof(final_score), "YOUR SCORE:  %d", g->si->score_1);
  si_text_display(g, final_score, 14, 6);
    
  // Affichage du meilleur score
    
  char best_score[50];
  snprintf(best_score, sizeof(best_score), "BEST SCORE:  %d", g->si->score_highest);
  si_text_display(g, best_score, 16, 6);

  // Màj du high score (si besoin)

  if(g->si->score_1 > g->si->score_highest)
    {
      g->si->score_highest = g->si->score_1;
      snprintf(best_score, sizeof(best_score), "NEW BEST:  %d", g->si->score_highest);
    }
  else
    {
      snprintf(best_score, sizeof(best_score), "HIGH SCORE:  %d", g->si->score_highest);
    }
  
  si_text_display(g, best_score, 18, 6);

  // Nombre de vagues atteintes
  
  char waves[50];
  
  snprintf(waves, sizeof(waves), "WAVES COMPLETED: %d",g->num_wave - 1);
  si_text_display(g, waves, 20, 4);

  // Instructions
  si_text_display(g, "PRESS ANY KEY TO EXIT", 25, 3);
  
}
