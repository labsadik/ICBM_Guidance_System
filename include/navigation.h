#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "types.h"

void update_position(Missile *m, Target *t, NavigationSystem *nav, double dt);
double get_distance_to_target(Missile *m, Target *t);
bool is_target_hit(Missile *m, Target *t);

#endif