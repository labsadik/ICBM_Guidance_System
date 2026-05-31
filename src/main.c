#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "../include/types.h"
#include "../include/navigation.h"
#include "../include/propulsion.h"
#include "../include/guidance.h"

void print_status(Missile *m, Target *t, NavigationSystem *nav, Warhead *w) {
    printf("\n=== RS-28 SARMAT (SATAN II) TELEMETRY ===\n");
    printf("Time: %.2f s | Phase: %d\n", m->time_elapsed, m->state);
    printf("Speed: Mach %.2f (%.2f m/s)\n", m->mach, m->speed);
    printf("Altitude: %.2f km | Dist To Tgt: %.2f km\n", 
           m->z / 1000.0, get_distance_to_target(m, t) / 1000.0);
    
    printf("NAV SYS: [RADAR: %s] [SAT: %s] [STELLAR: %s]\n",
           nav->radar_active ? "ON" : "OFF",
           nav->satellite_link_active ? "ON" : "OFF",
           nav->stellar_navigation_active ? "ON" : "OFF");

    printf("PAYLOAD: %s | Mass: %.1f kg | Warheads: %d\n", 
           w->type, w->yield_kg, w->warhead_count);
    printf("FUEL: %.2f%%\n", m->fuel);
    printf("========================================\n");
}

void receive_commander_orders(Target *t, Warhead *w) {
    printf("\n>>> CONNECTING TO STRATEGIC COMMAND (KREMLIN LINK)...\n");
    Sleep(1500);
    printf(">>> LINK SECURE. AUTHORIZATION CODE: ALPHA-OMEGA.\n");
    Sleep(1000);
    
    strcpy(t->id, "TGT-STRATEGIC-01");
    t->x = 16000000.0; 
    t->y = 12000000.0;
    
    strcpy(w->type, "MIRV Bus / Heavy");
    w->yield_kg = 8800.0;
    w->warhead_count = 15; 
    
    printf(">>> ORDER RECEIVED: LAUNCH RS-28 SARMAT\n");
    printf(">>> TARGET: %s (RANGE: 16,000 km)\n", t->id);
    printf(">>> PAYLOAD: %.1f kg (Avangard HGV Capable)\n", w->yield_kg);
    printf(">>> TRAJECTORY: POLAR (Evading Radar Coverage)\n\n");
    Sleep(1500);
}

int main() {
    srand(time(NULL));

    NavigationSystem nav_sys = {
        .radar_active = true,
        .satellite_link_active = true,
        .gyroscopic_ins_active = true, // Turned on so evasive logic works
        .stellar_navigation_active = false,
        .accuracy_meters = 5.0
    };

    Warhead payload = { .armed = false, .warhead_count = 0 };

    Missile sarmat = {
        .x = 0, .y = 0, .z = 0, .speed = 0, .distance_traveled = 0, 
        .mach = 0, .fuel = 100.0, .state = STATE_AWAITING_COMMAND,
        .time_elapsed = 0, .target_locked = 0
    };

    Target enemy_target;

    receive_commander_orders(&enemy_target, &payload);
    payload.armed = true;
    sarmat.state = STATE_LAUNCH;

    printf(">>> LAUNCH SEQUENCE INITIATED: SATAN II <<<\n");
    printf(">>> IGNITION. LIFTOFF. <<<\n\n");

    double dt = 0.5; 
    int print_counter = 0;

    while (1) {
        run_guidance_system(&sarmat, &enemy_target, &nav_sys);
        update_propulsion(&sarmat, dt);
        update_position(&sarmat, &enemy_target, &nav_sys, dt);

        double dist_to_tgt = get_distance_to_target(&sarmat, &enemy_target);
        
        if (dist_to_tgt < 500000 && sarmat.state == STATE_REENTRY) {
             printf("\n>>> TERMINAL PHASE. DECOYS RELEASED. <<<\n");
             printf(">>> SPEED MACH 25+. IMPACT IMMINENT. <<<\n\n");
             sarmat.state = STATE_TERMINAL;
        }

        sarmat.time_elapsed += dt;

        // Print telemetry every 1 second (2 ticks)
        print_counter++;
        if (print_counter >= 2) {
            print_status(&sarmat, &enemy_target, &nav_sys, &payload);
            print_counter = 0;
        }

        if (sarmat.state == STATE_TARGET_DESTROYED) {
            printf("\n\n>>> IMPACT CONFIRMED <<<\n");
            printf(">>> 8,800 kg PAYLOAD DETONATED <<<\n");
            printf(">>> TARGET VAPORIZED. STRIKE SUCCESSFUL. <<<\n");
            break;
        }

        if (sarmat.state == STATE_OUT_OF_RANGE || sarmat.fuel <= 0) {
            printf("\n>>> MISSION ABORT <<<\n");
            break;
        }
        
        Sleep(50); 
    }

    return 0;
}