// si_sdl.c
#include <SDL.h>
#include "../include/si_sdl.h"
#include "../include/si_font.h"


/**  Dessiner sprite **/

void si_display_sprite(Game *g, char *sprite, int w, int x, int y) {
  /* w = columns of sprite */
  /* (x,y) position in window of top left corner of sprite */
  
    int pixel_size = g->pixel_size;


    /* Sprite 8 rows */
    /* Iterate over sprite*/
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < w; col++) {
	  
	  /* Access to pixel (row, column)*/
            if (sprite[row * w + col]) {
	      /* Pixel On */
          /*SDL_Rect draws a square */
                SDL_Rect rect = {
                    x + col * pixel_size,
                    y + row * pixel_size,
                    pixel_size,
                    pixel_size // size of square pixel_size*pixel_size
                };
                /* Draw pixel white*/  
                SDL_SetRenderDrawColor(g->ren, 255, 255, 255, 255);
                SDL_RenderFillRect(g->ren, &rect);
            }
        }
    }
}





/** Text -- alphanum **/

/* Draw one character ASCII char c in position (x,y) position in window of top left corner of the character*/
void si_alphanum_display(Game *g, char c, int x, int y) {
    int width;
    char *sprite = si_font_alphanum_get(c, &width); 
    si_display_sprite(g, sprite, width, x, y);
}


/* Draw chain of text const char *str beginning in position (x,y)*/
void si_str_display(Game *g, const char *str, int x, int y) {
    int pos_x = x;
    
    // Iterate through each character of the string
    for (int i = 0; str[i] != '\0'; i++) {
        si_alphanum_display(g, str[i], pos_x, y);
        /* All characters ASCII have width=5 + 1 column in blank between characters */
        pos_x += 6 * g->pixel_size;
    }
}

/* Draw text str in line x col coordinates
line = row of the text
col = column where it begins
*/
void si_text_display(Game *g, const char *str, int line, int col) {
    int x = col * 6 * g->pixel_size;   // 6 = 5px + 1px space
    int y = line * 9 * g->pixel_size;  // 9 = 8px + 1px space
    si_str_display(g, str, x, y);
}


/** tank **/

void si_tank_display(Game *g, int x, int y) {
    int width;
    char *sprite = si_font_tank_get(&width);
    si_display_sprite(g, sprite, width, x, y);
}


void si_tank_explode_display(Game *g, int type, int x, int y)
{
    int width;
    char *sprite = si_font_tank_explode_get(type, &width);
    si_display_sprite(g, sprite, width, x, y);
}

void si_tank_shoot_display(Game *g, int x, int y)
{
    int width;
    char *sprite = si_font_tank_shoot_get(&width);
    si_display_sprite(g, sprite, width, x, y);
}

void si_tank_set_position(Game *g)
{
    if (!g || !g->si) return;

    int width;
    (void)si_font_tank_get(&width);   /* solo queremos el ancho lógico */

    int sprite_w_px = width * g->pixel_size;

    int x = (g->window_width - sprite_w_px) / 2;
    int y = g->window_height - 3 * g->pixel_size * 8;

    g->si->tank.x = x;



/** invader **/

void si_invader_display(Game *g, int type, int model, int x, int y) {
    int width;
    char *sprite = si_font_invader_get(type, model, &width);
    si_display_sprite(g, sprite, width, x, y);
}


void si_invader_explode_display(Game *g, int x, int y)
{
    int width;
    char *sprite = si_font_invader_explode_get(&width);
    si_display_sprite(g, sprite, width, x, y);
}

void si_invader_shoot_display(Game *g, int x, int y)
{
    int width;
    char *sprite = si_font_invader_shoot_get(&width);
    si_display_sprite(g, sprite, width, x, y);
}



/** ufo **/


void si_ufo_display(Game *g, int x, int y) {
    int width;
    char *sprite = si_font_ufo_get(&width);
    si_display_sprite(g, sprite, width, x, y);
}




/*Just for test without si_get_matrix*/

#define SI_INVADERS_ROWS 5
#define SI_INVADERS_COLS 11

void si_invaders_display(Game *g, int x, int y)
{
    int pixel = g->pixel_size;

    /* Tamaño de un invader en “real pixels” */
    int invader_w_px = 12 * pixel;  
    int invader_h_px = 8  * pixel;  /* 8 rows */

    /* Espacio entre invaders */
    int spacing_x = invader_w_px + 2 * pixel;
    int spacing_y = invader_h_px + 2 * pixel;

    for (int row = 0; row < SI_INVADERS_ROWS; ++row) {
        for (int col = 0; col < SI_INVADERS_COLS; ++col) {

            Si_Type t;
            if (row == 0)
                t = SI_TYPE_SQUID;     
            else if (row <= 2)
                t = SI_TYPE_CRAB;      
            else
                t = SI_TYPE_OCTOPUS;   

            int model = 0;  /* frame 0 */

            int ix = x + col * spacing_x;
            int iy = y + row * spacing_y;

            si_invader_display(g, t, model, ix, iy);
        }
    }
}


