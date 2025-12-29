#ifndef SI_FONT_H
#define SI_FONT_H


#include "si.h"



/* renvoie le sprite du caractère 'c', ainsi que sa largeur dans width 
Returns pointer to character ASCII with width
*/

char *si_font_alphanum_get(char c, int *width);

/* renvoie le sprite du tank, ainsi que sa largeur dans width */

char *si_font_tank_get(int *width);

/* renvoie le sprite de l’explosion du tank, ainsi que sa largeur dans width */

char *si_font_tank_explode_get(int type, int *width);

/* renvoie le sprite du tir du tank, ainsi que sa largeur dans width */

char *si_font_tank_shoot_get(int *width);

/* renvoie le sprite de l’UFO, ainsi que sa largeur dans width */

char *si_font_ufo_get(int *width);

/* renvoie le sprite de l’ennemi de type 't' et du modèle (pour
 l’animation), ainsi que sa largeur dans width */

char *si_font_invader_get(Si_Type t, int model, int *width);

/* renvoie le sprite de l’explosion d’un ennemi, ainsi que sa largeur dans width */

char *si_font_invader_explode_get(int *width);

/* renvoie le sprite du tir d’un ennemi, ainsi que sa largeur dans width */

char *si_font_invader_shoot_get(int *width);


#endif
