#include "main.h"

namespace shooter {
pros::Motor kicker(-20, pros::E_MOTOR_GEAR_RED);

void init() {
    kicker.set_gearing(MOTOR_GEARSET_36);
    kicker.set_encoder_units(MOTOR_ENCODER_DEGREES);
    printf("Shooter finished initialize\n");
}

bool is_moving = false;
double velocity = 300;

void opcontrol() {
    if (drive::master.get_digital_new_press(DIGITAL_B)) {
        is_moving = !is_moving;
    }
    if (is_moving) {
        kicker.move_velocity(velocity);
    }
}
}  // namespace shooter