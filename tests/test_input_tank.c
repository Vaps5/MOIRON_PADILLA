/*Test of the logic - movement of the bullet without SDL 
To compile

gcc -g -O2 -Wall -Wextra -I./include \
  -o test_input_tank \
  tests/test_input_tank.c src/si.c

./test_input_tank
*/

#include <stdio.h>
#include "../include/si.h"

/* Si structure without si_new*/
static void si_instance(Si *si)
{
    /* Sizes */
    si->window_width  = 800;
    si->window_height = 600;
    si->pixel_size    = 3;

    /*Initialize tank middle */
    si->tank.x = 400;
    si->tank.firing = 1;
    si->tank.shoot_x = 400;
    si->tank.shoot_y = 500;
    si->tank.destroyed = 0;
    si->tank.destroyed_count = 0;

    si->invaders.bomb_x = 0;
    si->invaders.bomb_y = 0;
    si->invaders.firing = 0;


    /* Player 1 has 3 lifes */
    si->life_1 = 3;
}

int main(void)
{
    Si si;
    si_instance(&si);

    printf("Test shoot up\n");

    while (si.tank.firing) {
        printf("Bullet y = %d\n", si.tank.shoot_y);
        si_tank_shoot_can_move_up(&si);
    }

    printf("Bullet stopped at y=%d\n", si.tank.shoot_y);

    return 0;
}