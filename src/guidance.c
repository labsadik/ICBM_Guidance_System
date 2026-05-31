#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // <--- ADDED THIS TO FIX THE WARNINGS
#include "../include/guidance.h"
#include "../include/types.h"
#include "../include/navigation.h"      
#include "../include/propulsion.h"      

int check_interceptor_presence(Missile *m) {
    if (m->state == STATE_REENTRY || m->state == STATE_TERMINAL) {
        if (m->fuel > 10.0) {
            int roll = rand() % 100;
            if (roll < 10) return 1;      
            if (roll < 15) return 5;      
        }
    }
    return 0;
}

void run_guidance_system(Missile *m, Target *t, NavigationSystem *nav) {
    if (m->distance_traveled >= MAX_RANGE) {
        m->state = STATE_OUT_OF_RANGE;
        return;
    }

    if (is_target_hit(m, t)) {
        m->state = STATE_TARGET_DESTROYED;
        return;
    }

    int threat_count = check_interceptor_presence(m);

    if (threat_count > 0) {
        m->state = STATE_EVASIVE;
        
        nav->radar_active = false;
        nav->stellar_navigation_active = true;
        
        if (threat_count > 1) {
            printf("!!! WARNING: HEAVY INTERCEPTOR BARRAGE (%d UNITS) !!!\n", threat_count);
            printf("!!! DEPLOYING SARMAT COUNTERMEASURES & MIRV DECOYS !!!\n");
            printf("!!! INITIATING UNPREDICTABLE JUGGLING TRAJECTORY !!!\n");
        } else {
            printf("!!! INTERCEPTOR LOCKED. SARMAT EVADING !!!\n");
        }
        activate_evasive_thrust(m);
    } else {
        if (m->state == STATE_EVASIVE) {
            if (rand() % 100 < 10) { 
                resume_cruise_thrust(m);
                nav->radar_active = true;
                nav->stellar_navigation_active = false;
                printf("!!! THREATS CLEARED. RESUMING BALLISTIC TRAJECTORY !!!\n");
            }
        }
    }
    
    // Trigger Re-entry based on distance traveled (Apogee)
    if (m->state == STATE_SUBORBITAL) {
        // Calculate total straight-line distance to target
        double total_initial_dist = sqrt(pow(t->x, 2) + pow(t->y, 2));
        
        // When missile has covered about 45% of the distance, it reaches apogee and falls
        if (m->distance_traveled > total_initial_dist * 0.45) {
            m->state = STATE_REENTRY;
            printf(">>> APOGEE REACHED. RE-ENTRY INITIATED. ATMOSPHERIC INTERFACE. <<<\n");
        }
    }
}