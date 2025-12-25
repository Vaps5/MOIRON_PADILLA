#include <stdio.h>
#include "../include/si.h"

/*Test of the logic - movement of the bullet without SDL 
To compile

gcc -g -O2 -Wall -Wextra -I./include \
  -o test_shots_timing \
  tests/test_shots_timing.c src/si.c

./test_shots_timing
*/


static void init_fake_si(Si *si)
{
    si->window_width = 800;
    si->window_height = 600;
    si->pixel_size = 3;

    si->tank.firing = 1;
    si->tank.shoot_y = 500;
}

int main(void)
{
    Si si;
    init_fake_si(&si);

    printf("=== Timing test ===\n");
    for (int step = 0; step < 200 && si.tank.firing; ++step) {
        si_tank_shoot_can_move_up(&si);
        if (step % 10 == 0) {
            printf("step=%d y=%d\n", step, si.tank.shoot_y);
        }
    }
    printf("done firing=%d y=%d\n", si.tank.firing, si.tank.shoot_y);
    return 0;
}
