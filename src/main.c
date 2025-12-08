#include <stdio.h>
#include <SDL.h>
#include "../include/si_font.h"

static SDL_Window *win = NULL;
static SDL_Renderer *renderer = NULL;
static int update = 1;


void pixel_update()
{
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); /* Fond noir */
  SDL_RenderClear(renderer);
    
  int pixel_size = 4; /* Taille d'un pixel en pixels réels */
  int start_x = 50;   /* Position de départ en X */
  int start_y = 50;   /* Position de départ en Y */
  int char_spacing = 12 * pixel_size; /* Espace entre les caractères */
    
  /* Fonction pour afficher un caractère */
  void display_char(char c, int x, int y) {
      int width;
      char *sprite = si_font_alphanum_get(c, &width); 
      /* ci-dessus, on donne une valeur à width */
      if (!sprite) return;
      for (int row = 0; row < 8; row++) /* 8 le nombre de lignes */
	{
          for (int col = 0; col < width; col++)
	    {
              int index = row * width + col;
              if (sprite[index])
        	{
		  /* mettre le pixel en blanc */
                    SDL_Rect pixel_rect =
		      {
                        x + col * pixel_size,
                        y + row * pixel_size,
                        pixel_size,
                        pixel_size,
		      };
		    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &pixel_rect);
		}
            }
        }
    }
    
    /* Fonction pour afficher sur l'écran */
    void display_string(const char *str, int x, int y) {
        for (int i = 0; str[i] != '\0'; i++) {
            display_char(str[i], x, y);
            x += char_spacing;
        }
    }
    
    // Afficher l'alphabet majuscule
    display_string("ABCDEFGHIJKLM", start_x, start_y);
    display_string("NOPQRSTUVWXYZ", start_x, start_y + char_spacing);
    
    // Afficher les chiffres
    display_string("0123456789", start_x, start_y + 2 * char_spacing);
    
    // Afficher les symboles
    display_string(" <>-*?=", start_x, start_y + 3 * char_spacing);
    
    // Afficher quelques mots de test
    display_string("SPACE INVADERS", start_x, start_y + 5 * char_spacing);
    display_string("HELLO WORLD!", start_x, start_y + 6 * char_spacing);
    display_string("TEST FONTS", start_x, start_y + 7 * char_spacing);
    
    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);
}



int main(int argc, char *argv[])
{
  SDL_Event events;
  int x; /* coord. x du coin haut gauche de la fenêtre */
  int y; /* coord. y du coin haut gauche de la fenêtre */
  int w; /* largeur de la fenêtre */
  int h; /* hauteur de la fenêtre */
  int ret = 1;
  int running;
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error : %s\n", SDL_GetError());
      goto err;
    }
  
  x = 60;
  y = 60;
  w = 800;
  h = 600;
  win = SDL_CreateWindow("game",x,y,w,h,SDL_WINDOW_SHOWN);
  
  if(win == NULL)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error : %s\n", SDL_GetError());
      goto sdl_quit;
    }
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error : %s\n", SDL_GetError());
      goto destroy_window;
    }
  
  /* creation des evenements */
  running = 1;
  while(running)
    {
      while(SDL_PollEvent(&events))
	{
	  switch(events.type)
	    {
	    case SDL_QUIT:
	      {
		running = 0;
		break;
	      }
	    case SDL_KEYDOWN:
	      {
		switch(events.key.keysym.sym)
		  {
		  case SDLK_q:
		    running = 0;
		    break;
		  }
		break;
	      }
	    }
	}
      if(update)
	pixel_update();
    }
  

  ret = 0;

  SDL_DestroyRenderer(renderer);
 destroy_window:
  SDL_DestroyWindow(win);
 sdl_quit:
  SDL_Quit();
 err:
  return ret;

  (void)argc;
  (void)argv;
}
