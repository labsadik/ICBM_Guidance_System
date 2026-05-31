#include <stdlib.h>
#include <stdio.h>
#include "../include/propulsion.h"
#include "../include/types.h"

void update_propulsion(Missile *m, double dt) {
    // Transition from LAUNCH to BOOST to fix the 0 speed bug
    if (m->state == STATE_LAUNCH) {
        m->state = STATE_BOOST;
    }

    m->mach = m->speed / SPEED_OF_SOUND;

    switch (m->state) {
        case STATE_BOOST:
            if (m->time_elapsed <= BOOST_PHASE_TIME) {
                double target_speed = 22.0 * SPEED_OF_SOUND; 
                double accel = target_speed / BOOST_PHASE_TIME;
                m->speed += accel * dt;
            } else {
                m->state = STATE_SUBORBITAL;
            }
            break;

        case STATE_SUBORBITAL:
            if (m->speed < 20.0 * SPEED_OF_SOUND) {
                m->speed += 10.0 * dt; 
            }
            break;

        case STATE_REENTRY:
            m->speed += 20.0 * dt; 
            break;

        case STATE_TERMINAL:
            {
                double target_speed = TERMINAL_BOOST_MACH * SPEED_OF_SOUND;
                if (m->speed < target_speed) {
                    m->speed += 100.0 * dt; 
                }
            }
            break;

        case STATE_EVASIVE:
            {
                double target_speed = ((double)(rand() % 90 + 150) / 10.0) * SPEED_OF_SOUND; // Mach 15-24
                if (m->speed < target_speed) {
                    m->speed += 50.0 * dt;
                }
            }
            break;
        
        default:
            break;
    }

    double burn_rate = (m->mach / 20.0) * 0.005 * dt; 
    m->fuel -= burn_rate;
    if (m->fuel < 0) m->fuel = 0;
}

void activate_evasive_thrust(Missile *m) {
    m->state = STATE_EVASIVE;
}

void resume_cruise_thrust(Missile *m) {
    m->state = STATE_REENTRY;
}