#include "main.h"

namespace wings {
pros::ADIAnalogOut left_front_wing('A');
pros::ADIAnalogOut right_front_wing('B');
pros::ADIAnalogOut left_back_wing('C');
pros::ADIAnalogOut right_back_wing('D');

void init() {
    left_front_wing.set_value(0);
    right_front_wing.set_value(0);
    left_back_wing.set_value(0);
    right_back_wing.set_value(0);
}

void front_wings(bool state) {
    if (state) {
        left_front_wing.set_value(1);
        right_front_wing.set_value(1);
    } else {
        left_front_wing.set_value(0);
        right_front_wing.set_value(0);
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

void opcontrol() {
    if (drive::master.get_digital(DIGITAL_L1)) {
        front_wings(true);
    } else {
        front_wings(false);
    }
    if (drive::master.get_digital(DIGITAL_L2)) {
        back_wings(true);
    } else {
        back_wings(false);
    }
}
}  // namespace wings