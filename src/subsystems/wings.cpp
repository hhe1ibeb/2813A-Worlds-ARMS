#include "main.h"

namespace wings {
pros::ADIDigitalOut left_front_wing('A');
pros::ADIDigitalOut right_front_wing('B');
pros::ADIDigitalOut left_back_wing('C');
pros::ADIDigitalOut right_back_wing('D');

pros::ADIDigitalOut wings('G');

void init() {
    left_front_wing.set_value(0);
    right_front_wing.set_value(0);
    left_back_wing.set_value(0);
    right_back_wing.set_value(0);
}

void front_wings(bool state) {
    if (state) {
        wings.set_value(1);
        // left_front_wing.set_value(1);
        // right_front_wing.set_value(1);
    } else {
        wings.set_value(0);
        // left_front_wing.set_value(0);
        // right_front_wing.set_value(0);
    }
}

void back_wings(bool state) {
    if (state) {
        left_back_wing.set_value(1);
        right_back_wing.set_value(1);
    } else {
        left_back_wing.set_value(0);
        right_back_wing.set_value(0);
    }
}

bool is_on = false;

void opcontrol() {
    // if (drive::master.get_digital_new_press(DIGITAL_L1)) {
    //     front_wings(true);
    // } else {
    //     front_wings(false);
    // }
    // if (drive::master.get_digital_new_press(DIGITAL_L2)) {
    //     back_wings(true);
    // } else {
    //     back_wings(false);
    // }

    if (drive::master.get_digital_new_press(DIGITAL_L1)) {
        is_on = !is_on;
    }

    if (is_on) {
        wings.set_value(1);
    } else {
        wings.set_value(0);
    }
}
}  // namespace wings