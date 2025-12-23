#include <stdio.h>
#include "../include/si_menu.h"
#include "../include/si_sdl.h"

// A MODIF QUAND GAME.C SERA FINI

void menu(Game *g)
{
  si_text_display(g, "SCORE<1> HI-SCORE SCORE<2>", 1, 1);
  si_text_display(g, "0000     0000     0000", 3, 3);
  si_text_display(g, "PLAY", 7, 13);
  si_text_display(g, "SPACE  INVADERS", 10, 8);
  si_text_display(g, "*SCORE ADVANCE TABLE*", 14, 3);
  si_text_display(g, "CREDIT", 29, 11);
}

void game_over(Game *g)
{
    si_text_display(g, "GAME OVER", 15, 8);
    
    // Affichage du score final
    
    char final_score[50];
    snprintf(final_score, sizeof(final_score), "FINAL SCORE: %d", g->si->score_1);
    si_text_display(g, final_score, 17, 6);
    
    // Affichage du meilleur score
    
    char best_score[50];
    snprintf(best_score, sizeof(best_score), "BEST SCORE: %d", g->si->score_highest);
    si_text_display(g, best_score, 18, 7);
    
    // Mise à jour du high score (si besoin)
    
    if(g->si->score_1  >  g->si->score_highest)
      {
        g->si->score_highest = g->si->score_1;
      }
}
