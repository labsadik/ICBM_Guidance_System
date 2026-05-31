#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

// RS-28 Sarmat (Satan II) Constants
#define SPEED_OF_SOUND 343.0
#define MAX_RANGE 18000000.0     // 18,000 km (Sarmat Range)
#define BOOST_PHASE_TIME 60.0    // Longer boost for ICBM
#define CRUISE_SPEED_MACH 20.0   // Hypersonic Cruise
#define EVASIVE_MIN_MACH 15.0
#define EVASIVE_MAX_MACH 24.0
#define TERMINAL_BOOST_MACH 27.0

typedef enum {
    STATE_IDLE,
    STATE_AWAITING_COMMAND,
    STATE_LAUNCH,
    STATE_BOOST,
    STATE_SUBORBITAL,
    STATE_REENTRY,
    STATE_EVASIVE,          
    STATE_TERMINAL,
    STATE_TARGET_DESTROYED,
    STATE_OUT_OF_RANGE
} MissileState;

typedef struct {
    double x;
    double y;
    char id[20];
} Target;

typedef struct {
    double x;
    double y;
    int threat_level;
} Interceptor;

typedef struct {
    double x;
    double y;
    double z;
    double speed;
    double distance_traveled;
    double mach;
    double fuel;
    MissileState state;
    double time_elapsed;
    int target_locked;
} Missile;

typedef struct {
    bool radar_active;
    bool satellite_link_active;
    bool gyroscopic_ins_active;
    bool stellar_navigation_active;
    double accuracy_meters;
} NavigationSystem;

typedef struct {
    char type[30];
    double yield_kg;
    int warhead_count;
    bool armed;
} Warhead;

#endif