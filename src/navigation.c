#include <math.h>
#include "../include/navigation.h"
#include "../include/types.h"
#include <stdio.h>
#include <stdlib.h>

void update_position(Missile *m, Target *t, NavigationSystem *nav, double dt) {
    if (m->state == STATE_IDLE || m->state == STATE_AWAITING_COMMAND || m->state == STATE_TARGET_DESTROYED) {
        return;
    }

    double move_step = m->speed * dt;

    // --- CALCULATE ANGLE PER COURSE (Yaw to Target) ---
    double dx = t->x - m->x;
    double dy = t->y - m->y;
    double h_dist = sqrt(dx*dx + dy*dy);
    
    double ux = 0, uy = 0;
    if (h_dist > 0) {
        ux = dx / h_dist; // Normalized X direction
        uy = dy / h_dist; // Normalized Y direction
    }

    // --- HORIZONTAL MOVEMENT ---
    if (m->state == STATE_EVASIVE && nav->gyroscopic_ins_active) {
        // Juggling / Evasive Logic
        double jitter_strength = 3000.0; 
        double jitter_x = ((double)rand() / RAND_MAX - 0.5) * jitter_strength;
        double jitter_y = ((double)rand() / RAND_MAX - 0.5) * jitter_strength;
        
        m->x += move_step * ux * 0.9 + jitter_x * dt;
        m->y += move_step * uy * 0.9 + jitter_y * dt;
    } else {
        // Standard Ballistic Path aimed at target
        m->x += move_step * ux * 0.9;
        m->y += move_step * uy * 0.9;
    }

    // --- ALTITUDE LOGIC (Pitch Arc) ---
    // Simulate a realistic ICBM arc (Peak ~1200 km)
    double target_alt = 0;
    if (m->state == STATE_LAUNCH || m->state == STATE_BOOST) {
        target_alt = 500000; // 500 km during boost
    } else if (m->state == STATE_SUBORBITAL) {
        target_alt = 1200000; // 1200 km in space
    } else if (m->state == STATE_REENTRY || m->state == STATE_TERMINAL) {
        target_alt = 0; // Descend to ground
    } else if (m->state == STATE_EVASIVE) {
        target_alt = 800000; // Mid-air juking
    }
    
    // Smoothly adjust altitude towards target profile
    if (m->z < target_alt) {
        m->z += move_step * 0.5;
        if (m->z > target_alt) m->z = target_alt;
    } else if (m->z > target_alt) {
        m->z -= move_step * 0.4; // Fall faster
        if (m->z < target_alt) m->z = target_alt;
    }

    m->distance_traveled += move_step;
}

double get_distance_to_target(Missile *m, Target *t) {
    return sqrt(pow(t->x - m->x, 2) + pow(t->y - m->y, 2));
}

bool is_target_hit(Missile *m, Target *t) {
    double dist = get_distance_to_target(m, t);
    return (dist < 100.0 && m->z <= 0);
}