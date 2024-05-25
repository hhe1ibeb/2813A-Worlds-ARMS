#ifndef _ARMS_CONFIG_H_
#define _ARMS_CONFIG_H_

#include "ARMS/api.h"

namespace arms {

// Debug
#define ODOM_DEBUG 0

// Negative numbers mean reversed motor
#define LEFT_MOTORS -17, -18, -19
#define RIGHT_MOTORS 12, 13, 14
#define GEARSET pros::E_MOTOR_GEAR_600  // RPM of chassis motors

// Ticks per inch
#define TPI 32.54     // Encoder ticks per inch of forward robot movement
#define MIDDLE_TPI 1  // Ticks per inch for the middle wheel

// Tracking wheel distances
#define TRACK_WIDTH \
    12.7  // The distance between left and right wheels (or tracker wheels)
#define MIDDLE_DISTANCE \
    0  // Distance from middle wheel to the robot turning center

// Sensors
#define IMU_PORT 16                           // Port 0 for disabled
#define ENCODER_PORTS 0, 0, 0                 // Port 0 for disabled,
#define EXPANDER_PORT 0                       // Port 0 for disabled
#define ENCODER_TYPE arms::odom::ENCODER_ADI  // The type of encoders

// Movement tuning
#define SLEW_STEP 8              // Smaller number = more slew
#define LINEAR_EXIT_ERROR 1      // default exit distance for linear movements
#define ANGULAR_EXIT_ERROR 1     // default exit distance for angular movements
#define SETTLE_THRESH_LINEAR .5  // amount of linear movement for settling
#define SETTLE_THRESH_ANGULAR 1  // amount of angular movement for settling
#define SETTLE_TIME 250          // amount of time to count as settled
#define LINEAR_KP 15
#define LINEAR_KI 0
#define LINEAR_KD 0
#define TRACKING_KP 60  // point tracking turning strength
#define ANGULAR_KP 1.2
#define ANGULAR_KI 0
#define ANGULAR_KD 6
#define MIN_ERROR \
    5  // Minimum distance to target before angular componenet is disabled
#define LEAD_PCT .2          // Go-to-pose lead distance ratio (0-1)
#define MIN_LINEAR_SPEED 0   // Minimum speed for linear movements
#define MIN_ANGULAR_SPEED 0  // Minimum speed for angular movements

// Auton selector configuration constants
#define AUTONS \
    "NQ", "FQAWP", "FQN", "NE", "FE", "Nothing"  // Names of autonomi, up to 10
#define HUE 317    // Color of theme from 0-359(H part of HSV)
#define DEFAULT 6  // Default auton selected

// Initializer
inline void init() {
    chassis::init({LEFT_MOTORS}, {RIGHT_MOTORS}, GEARSET, SLEW_STEP,
                  LINEAR_EXIT_ERROR, ANGULAR_EXIT_ERROR, SETTLE_THRESH_LINEAR,
                  SETTLE_THRESH_ANGULAR, SETTLE_TIME, MIN_LINEAR_SPEED,
                  MIN_ANGULAR_SPEED);

    odom::init(ODOM_DEBUG, ENCODER_TYPE, {ENCODER_PORTS}, EXPANDER_PORT,
               IMU_PORT, TRACK_WIDTH, MIDDLE_DISTANCE, TPI, MIDDLE_TPI);

    pid::init(LINEAR_KP, LINEAR_KI, LINEAR_KD, ANGULAR_KP, ANGULAR_KI,
              ANGULAR_KD, TRACKING_KP, MIN_ERROR, LEAD_PCT);

    const char* b[] = {AUTONS, ""};
    selector::init(HUE, DEFAULT, b);
    printf("ARMS finished initialize\n");
}

}  // namespace arms

#endif