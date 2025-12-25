#include <stdlib.h>
#include "../include/si.h"

#define TANK_WIDTH_PIXELS   13   /* width tank sprite in pixels */
#define TANK_HEIGHT_PIXELS  8    /* height tank sprite */
#define TANK_SHOOT_SPEED    4    /* tank bullet speed per tick */


char matrice[5][11] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2},
    {3,3,3,3,3,3,3,3,3,3,3}, // GLOBAL MATRIX containing ennemies,
    {3,3,3,3,3,3,3,3,3,3,3}, // 0 = dead ennemies and 1,2,3 are alive ennemies
  };

/* crée un pointeur vers la structure Si. On passe en paramètre
 * les dimensions de la fenêtre et la taille de pixel */

Si *si_new(int window_width, int window_height, int pixel_size)
{
    Si *si = malloc(sizeof(Si));
    if (!si) {
        return NULL;
    }

    si->window_width  = window_width;
    si->window_height = window_height;
    si->pixel_size    = pixel_size;

    si->nbr_players   = 1;
    si->score_1       = 0;
    si->life_1        = 3;
    si->score_2       = 0;
    si->life_2        = 0;
    si->score_highest = 0;

    /* Tank initial state */
    si->tank.x               = window_width / 2;
    si->tank.firing          = 0;
    si->tank.shoot_x         = 0;
    si->tank.shoot_y         = 0;
    si->tank.destroyed       = 0;
    si->tank.destroyed_count = 0;

    /* Invaders initial state (will be refined later) */
    si->invaders.x         = 0;
    si->invaders.y         = 0;
    si->invaders.direction = 1;
    si->invaders.firing    = 0;
    si->invaders.bomb_x    = 0;
    si->invaders.bomb_y    = 0;

    return si;
}

/* Détruit les ressources */
void si_del(Si *si)
{
    if (si) {
        free(si);
    }
}

/* renvoie la matrice */
char *si_get_matrix(void)
{
  return (char *)matrice; 
}

/* renvoie le nombre d’ennemis restant dans la matrice */
int si_matrix_count(void)
{
  int count = 0;
  for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 11; j++)
	{
          if(matrice[i][j] != 0)
	    {
              count++;
            }
        }
    }
  return count;
}

/* renvoie le nombre de points en fonction de l’ennemi */
int si_get_points(Si_Type t)
{
    switch (t) {
    case SI_TYPE_SQUID:   return 30;
    case SI_TYPE_CRAB:    return 20;
    case SI_TYPE_OCTOPUS: return 10;
    }
    return 0;
}

/* renvoie le nombre de joueurs */
int si_get_nbr_players(Si *si)
{
    if (!si) return 0;
    return si->nbr_players;
}


/* teste si le tank peut se déplacer vers le haut. SI c’est possible,
   met à jour la coordonnée y du tir du Tank.*/
int si_tank_shoot_can_move_up(Si *si)
{
    if (!si) return 0;

    Tank *t = &si->tank;

    /* If no bullet is active, nothing to move */
    if (!t->firing) {
        return 0;
    }

    /* Move bullet upward */
    int new_y = t->shoot_y - TANK_SHOOT_SPEED;

    /* Deactivation when Bullet goes outside the screen */
    if (new_y < 0) {
        t->firing = 0;
        return 0;
    }

    /* Update position */
    t->shoot_y = new_y;
    return 1;
}

/* renvoie 1 si le tank est touché, 0 sinon */
int si_tank_is_hit(Si *si)
{
    if (!si) return 0;

    Tank *t = &si->tank;
    Invaders *inv = &si->invaders;

    /* no bomb */
    if (!inv->firing) return 0;
    /* already destroyed */     
    if (t->destroyed) return 0;     

    int pixel = si->pixel_size;

    /* Tank position on screen (Y is fixed near the bottom) */
    int tank_x = t->x;
    int tank_w = TANK_WIDTH_PIXELS  * pixel;
    int tank_h = TANK_HEIGHT_PIXELS * pixel;
    int tank_y = si->window_height - 4 * pixel * 8;

    /* Bomb */
    int bx = inv->bomb_x;
    int by = inv->bomb_y;

    int inside_x = (bx >= tank_x) && (bx <= tank_x + tank_w);
    int inside_y = (by >= tank_y) && (by <= tank_y + tank_h);

    if (inside_x && inside_y) {
        /* Tank is hit */
        t->destroyed       = 1;
        t->destroyed_count = 0;
        si->life_1--;

        return 1;
    }

    return 0;
}


void si_invaders_get_column(Si *si)
{
  int col = (rand() % 11);     // Renvoie une colonne aléatoire entre 0 et 10
                                  // On cherche l'ennemi vivant le plus bas dans la colonne
  for (int ligne = 4; ligne >= 0; ligne--) {  // On part du bas de la matrice (ligne 4) vers le haut
      if (matrice[ligne][col] != 0)
	{                                  // On calcule les coordonnées de la bombe à partir de l'ennemi vivant :
	  int largeur_ennemi = 12;         // Chaque ennemi est une matrice 12x8
          si->invaders.bomb_x = si->invaders.x + (col * largeur_ennemi) + (largeur_ennemi / 2) - 2; // -2 pour centrer le sprite de bombe 
          int hauteur_ennemi = 8;
          si->invaders.bomb_y = si->invaders.y + (ligne * hauteur_ennemi) + hauteur_ennemi;
            
          // On indique qu'une bombe a été lancée
          si->invaders.firing = 1;
          return;
        }
    }
    
    // si y a plus d'ennemis on lance pas de bombes
    si->invaders.firing = 0;
}

// Renvoie 1 si la bombe peut aller vers le bas et modifie sa position, 0 sinon 
int si_invaders_bomb_can_move_down(Si *si)
{
  int y = si->invaders.bomb_y - 8;// Pour avoir le plus bas pixel du sprite (voir si_font.c)
  if(si->window_height - y <= 0)      // Si la bombe est en bas de l'écran 
    return 0;
  si->invaders.bomb_y -= 1;            // Sinon la bombe descends.
  return 1;
}


int si_invaders_can_move_left(Si *si)
{
  int x =si->invaders.x;
  if(x == 0)     // si le coin haut-gauche de la matrice est tout à gauche de la fenetre
    return 0;    // la matrice ne peut pas se déplacer à gauche
  si->invaders.x -= 1; //sinon on update la position
  return 1;
}

// meme principe vers la droite

int si_invaders_can_move_right(Si *si)
{
  int x =si->invaders.x;
  if(x == si->window_width)
    return 0; 
  si->invaders.x += 1; 
  return 1;
}

int si_invader_is_hit(Si *si)
{
    int largeur_ennemi = 12;
    int hauteur_ennemi = 8;
    
    if (!si->tank.firing)
      {
        return 0;
      }
    // Coordonnées du tir du tank  
    int tir_x = si->tank.shoot_x;
    int tir_y = si->tank.shoot_y;
    
    // On vérifie si le tir touche un ennemi
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++)
	  {
            // Si l'ennemi est encore vivant
            if (matrice[i][j] != 0)
	      {
                // Calcul des coordonnées de l'ennemi
                int ennemi_x = si->invaders.x + (j * largeur_ennemi);
                int ennemi_y = si->invaders.y + (i * hauteur_ennemi);

		//on regarde si les sprites du tir et l'ennemi se superposent(se touchent)
                if(tir_x >= ennemi_x && tir_x < ennemi_x + largeur_ennemi)
		  {
                    if(tir_y >= ennemi_y && tir_y < ennemi_y + hauteur_ennemi)
		      {
                        
                        // update du score
                        Si_Type type = matrice[i][j];
                        switch (type)
			  {
                            case SI_TYPE_SQUID:
                                si->score_1 += 30;
                                break;
                            case SI_TYPE_CRAB:
                                si->score_1 += 20;
                                break;
                            case SI_TYPE_OCTOPUS:
                                si->score_1 += 10;
                                break;
                          }
			
			// ennemi détruit
                        matrice[i][j] = 0;
                        
                        // update du statut du tir
                        si->tank.firing = 0;
			
                        return 1;  // Un ennemi a été touché
                    }
                }
            }
        }
    }
    
    return 0;  // Aucun ennemi touché
}


// F4.B gestion des vagues


void si_reset_matrix(Si *si)
{
  char *mat = si_get_matrix();

  // on réinitialise la matrice
  
  for(int i = 0; i<5; i++)
    {
      for(int j = 0; j<11; j++)
	{
	  if(i == 0)
	    mat[i*11 + j] = 1;
	  if(i == 1 || i == 2)
	    mat[i*11 + j] = 2;
	  if(i == 3 || i == 4)
	    mat[i*11 + j] = 3;
	}
    }

  // et sa position
  
  si->invaders.x = 0;
  si->invaders.y = 0;
  si->invaders.direction = 1;
}


void si_new_wave(Si *si, float *enemy_speed, float *shoot_speed)
{
    si_reset_matrix(si);
    *enemy_speed *= 0.85;  // ennemis 15% plus rapide
    *shoot_speed *= 0.9;   // tirs 10% plus rapide    (potentiellement à changer plus tard après les tests)
}
