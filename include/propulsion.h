#ifndef PROPULSION_H
#define PROPULSION_H

#include "types.h"

void update_propulsion(Missile *m, double dt);
void activate_evasive_thrust(Missile *m);
void resume_cruise_thrust(Missile *m);

#endif