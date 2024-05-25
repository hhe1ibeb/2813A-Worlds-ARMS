#include "main.h"

namespace leds {

sylib::Addrled left(22, 8, 9);
sylib::Addrled right(22, 5, 9);

const int DISABLED_COLOR_START = 0xFF0000;
const int DISABLED_COLOR_END = 0x0077B6;

const int AUTON_COLOR_START = 0xFE5D9F;
const int AUTON_COLOR_END = 0xF5D2E6;

const int OPCONTROL_COLOR_START = 0xD8EBFF;
const int OPCONTROL_COLOR_END = 0x004589;

const int speed = 5;

void disabled() {
    left.gradient(DISABLED_COLOR_START, DISABLED_COLOR_END);
    right.gradient(DISABLED_COLOR_START, DISABLED_COLOR_END);
}

void disabled_cycle() {
    left.cycle(*left, 3);
    right.cycle(*right, 3);
}

void auton_set() {
    left.gradient(AUTON_COLOR_START, AUTON_COLOR_END);
    right.gradient(AUTON_COLOR_START, AUTON_COLOR_END);
}

void auton_cycle() {
    left.cycle(*left, speed);
    right.cycle(*right, speed);
}

void set() {
    left.gradient(OPCONTROL_COLOR_START, OPCONTROL_COLOR_END);
    right.gradient(OPCONTROL_COLOR_START, OPCONTROL_COLOR_END);
}
void cycle() {
    left.cycle(*left, speed);
    right.cycle(*right, speed);
}

void pulse() {
    left.pulse(0xFF36FF, 2, 10);
    right.pulse(0xFF36FF, 2, 10);
}

void pulse(std::vector<double> color, bool direction) {
    left.pulse(sylib::Addrled::rgb_to_hex(color[0], color[1], color[2]), 2, 10,
               0, direction);
    right.pulse(sylib::Addrled::rgb_to_hex(color[0], color[1], color[2]), 2, 10,
                0, direction);
}
}  // namespace leds