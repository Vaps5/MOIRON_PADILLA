//game.c
static void game_update(Game *g)
{
    SDL_SetRenderDrawColor(g->ren, 0x2b, 0x2a, 0x33, 0xff);
    SDL_RenderClear(g->ren);
    /* TODO : afficher la bannière (la première ligne et les scores) */
    if (!g->play_game)
    {
        menu(g);
    }
    else if (g->si->life_1 == 0)
    {
        game_over(g);
    }
    else
    {
        /* TODO : afficher les ennemis */
        /* TODO : si les ennemis tirent, afficher le tir */
        /* TODO : afficher le tank */
        /* TODO : si le tank tire, afficher le tir */
    }
    /* TODO : afficher la dernière ligne : le nombre de vies restant */
    SDL_RenderPresent(g->ren);

    /* fin de la mise à jour */
    g->update = 0;
}

Game *game_new(int x, int y)
{
    /* TODO : définir tous les membres */
}

void game_del(Game *g)
{
    /* TODO : a faire */
}
