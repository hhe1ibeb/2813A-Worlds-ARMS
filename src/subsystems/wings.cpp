#include "main.h"

namespace wings {
pros::ADIDigitalOut left_front_wing('A');
pros::ADIDigitalOut right_front_wing('B');
pros::ADIDigitalOut left_back_wing('C');
pros::ADIDigitalOut right_back_wing('D');

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

bool front_state = false;
bool back_state = false;

void opcontrol() {
    if (drive::master.get_digital_new_press(DIGITAL_L1)) {
        front_state = !front_state;
    }
    if (drive::master.get_digital_new_press(DIGITAL_L2)) {
        back_state = !back_state;
    }
    front_wings(front_state);
    back_wings(back_state);
}
}  // namespace wings