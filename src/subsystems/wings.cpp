#include "main.h"

namespace wings {
pros::ADIDigitalOut left_front_wing('A');
pros::ADIDigitalOut right_front_wing('C');
pros::ADIDigitalOut left_back_wing('B');
pros::ADIDigitalOut right_back_wing('D');

pros::ADIDigitalOut pto('F');
pros::ADIDigitalOut release('G');

void init() {
    left_front_wing.set_value(0);
    right_front_wing.set_value(0);
    left_back_wing.set_value(0);
    right_back_wing.set_value(0);
    printf("Wings finished initialize\n");
}

void front(bool state) {
    if (state) {
        left_front_wing.set_value(1);
        right_front_wing.set_value(1);
    } else {
        left_front_wing.set_value(0);
        right_front_wing.set_value(0);
    }
}

void back(bool state) {
    if (state) {
        left_back_wing.set_value(1);
        right_back_wing.set_value(1);
    } else {
        left_back_wing.set_value(0);
        right_back_wing.set_value(0);
    }
}

void front(bool right, bool left) {
    right_front_wing.set_value(right);
    left_front_wing.set_value(left);
}

void back(bool right, bool left) {
    right_back_wing.set_value(right);
    left_back_wing.set_value(left);
}

bool front_state = false;
bool back_state = false;
bool pto_state = false;
bool release_state = false;

void opcontrol() {
    if (drive::master.get_digital_new_press(DIGITAL_L1)) {
        front_state = !front_state;
    }
    if (drive::master.get_digital_new_press(DIGITAL_L2)) {
        back_state = !back_state;
    }
    if (drive::master.get_digital_new_press(DIGITAL_Y)) {
        pto_state = !pto_state;
    }
    if (drive::master.get_digital(DIGITAL_LEFT) &&
        drive::master.get_digital(DIGITAL_A)) {
        release_state = !release_state;
        pros::delay(500);
    }
    pto.set_value(pto_state);
    release.set_value(release_state);
    front(front_state);
    back(back_state);
}
}  // namespace wings