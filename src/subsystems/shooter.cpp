#include "main.h"

namespace shooter {
pros::Motor kicker(-20, pros::E_MOTOR_GEAR_RED);

void move(double velocity) { kicker.move_velocity(velocity); }

bool is_moving = false;
double velocity = 300;

void opcontrol() {
    if (drive::master.get_digital_new_press(DIGITAL_UP)) {
        velocity += 10;
    }
    if (drive::master.get_digital_new_press(DIGITAL_DOWN)) {
        velocity -= 10;
    }
    if (drive::master.get_digital_new_press(DIGITAL_A)) {
        is_moving = !is_moving;
    }
    if (is_moving) {
        kicker.move_velocity(velocity);
    }
}
}  // namespace shooter