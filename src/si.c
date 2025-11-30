#include <stdlib.h>
#include "../include/si.h"

#define TANK_WIDTH_PIXELS   13   /* width tank sprite in pixels */
#define TANK_HEIGHT_PIXELS  8    /* height tank sprite */
#define TANK_SHOOT_SPEED    4    /* tank bullet speed per tick */



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
    return NULL;
}

/* renvoie le nombre d’ennemis restant dans la matrice */
int si_matrix_count(void)
{
    return 0;
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

/* tank F4.1 A */

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

/* invaders F4.2-B */
