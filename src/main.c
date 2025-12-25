#include "../include/game.h"

int main(int argc, char *argv[])
{
  Game *g;

  g = game_new();
  if (!g)
    return 1;

  game_run(g);
  game_del(g);

  (void)argc;
  (void)argv;
  return 0;
}
