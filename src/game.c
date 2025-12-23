#include "../include/game.h"

static void game_update(Game *g)
{
    SDL_SetRenderDrawColor(g->ren, 0x2b, 0x2a, 0x33, 0xff);
    SDL_RenderClear(g->ren);

    // F4
    
    // Affichage du numéro de vague
    
    char wave[15];
    snprintf(wave, sizeof(wave), "WAVE: %d", g->current_wave);
    si_text_display(g, wave, 1, 10); // à changer si besoin (voir apres les tests)
    
    // Affichage du meilleur score
    
    char high_score[50];
    snprintf(high_score, sizeof(high_score), "HIGH: %d", g->si->score_highest);
    si_text_display(g, high_score, 1, 18); // à changer si besoin (voir apres les tests)
    
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
    
    // Affichage nombre de vies restantes
    
    char lives[20];
    snprintf(lives, sizeof(lives), "LIVES: %d", g->si->life_1);
    si_text_display(g, lives, 28, 0);

    SDL_RenderPresent(g->ren);

    /* fin de la mise à jour */
    g->update = 0;
}

Game *game_new(int x, int y)
{
  /* TODO : définir tous les membres */
  
  // F4
  g->current_wave = 1;
  g->invaders_speed = 0.1;  // Vitesse initiale
  g->shoot_speed = 0.005;   // Vitesse initiale des tirs
}

void game_del(Game *g)
{
    /* TODO : a faire */
}

void game_run(Game *g)
{
  int running;
  running 1;
  while (running)
    {
      SDL_Events events;
      Uint64 c_shoot;
      Uint64 c_invaders;

      while (SDL_PollEvent(&events))
	{
	  switch (events.type)
	    {
	    case SDL_QUIT:
	      {
		running = 0;
		break;
	      }
	    case SDL_KEYDOWN:
	      {
		switch (events.key.keysym.sym)
		  {
		  case SDLK_q:
		    {
		      running = 0;
		      break;
		    }
		  case SDLK_ESCAPE:
		    {
		      running = 0;
		      break;
		    }
		    /* TODO : gérer la touche Espace
		     * si ’play_game’ est vrai, on
		     * met à jour les coordonnées du tir
		     * sinon on met play_game à vrai et on
		     * met à jour
		     */
		  }
		break;
	      }
	    case SDL_MOUSEMOTION:
	      {
		/*sauvegarde de la nouvelle coordonnée x du tank puis mise à jour */
		int new_x = event.motion.x;
		g->si->tank.x = new_x;
		break;
	      }
	    }
	}
      if (g->play_game == 0)
	{
	  g->update = 1;
	}
      else
	{
	  c_invaders = SDL_GetPerformanceCounter();
	  c_shoot = SDL_GetPerformanceCounter();

	  /* animation lente pour les ennemis */
	  if ((float)(c_invaders - g->count_invaders) / g->freq > 0.1)
	    {
	      if (g->si->tank.destroyed)
		{
		  /*
		   * TODO: faire l’animation de l’explosion
		   * puis remettre à jour la position, le fait
		   * d’être d\’etruit, etc...
		   */
		}
	      else
		{
		  if (g->si->invades.direction == 1)
		    {
		      if (si_invaders_can_move_right(g->si))
			{
			  g->update = 1;
			}
		    }
		  else
		    {
		      if (si_invaders_can_move_left(g->si))
			{
			  g->update = 1;
			}
		    }
		}
	      g->count_invaders = c_invaders;
	    }
	  /* animation rapide pour les 2 tirs */
	  if ((float)(c_shoot - g->count_shoot) / g->freq > 0.005)
	    {
	      /* si le tank tire ... */
	      if (g->si->tank.firing)
		{
		  if (si_tank_shoot_can_move_up(g->si))
		    {
		      g->update = 1;
		    }
		}
	      /* si les ennemis ne tire pas ... */
	      if (!g->si->invaders.firing)
		{
		  /* on trouve une colonne aléatoirement */
		  si_invaders_get_column(g->si);

		  /* et on dit que les ennemi ont tiré */
		  g->si->invaders.firing = 1;
		}
	      /* si les ennemis ont tirés */
	      if (g->si->invaders.firing)
		{
		  /*
		   * si la bombe peut descendre, on la déplace et
		   * on met à jour
		   */
		  if (si_invaders_bomb_can_move_down(g->si))
		    {
		      g->update = 1;
		    }
		}
	      g->count_shoot = c_shoot;
	    }
	}
      if (g->update)
	game_update(g);
    }
}
		  
	  
      
