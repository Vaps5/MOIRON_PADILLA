#include <stdio.h>
#include "../include/si_menu.h"
#include "si_sdl.h"
#include "si_sdl.c"

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
  si_text_display(g, "SCORE<1> HI-SCORE SCORE<2>", 1, 1);
  si_text_display(g, "0000     0000     0000", 3, 3);
  si_text_display(g, "GAME OVER", 14, 8); // à modifier apres les tests
}
