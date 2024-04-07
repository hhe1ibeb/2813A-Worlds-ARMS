#include "main.h"

namespace sensors {
pros::Optical intake_optical(12);
pros::Distance intake_distance(14);

std::vector<double> get_color() {
    int hue = intake_optical.get_hue();
    std::vector<double> color = {255, 255, 255};
    if (abs(hue - 110) < 10) {
        color = {0, 255, 0};
    } else if (abs(hue - 220) < 30) {
        color = {0, 0, 255};
    } else if (abs(hue - 350) < 10 || abs(hue - 0) < 10) {
        color = {255, 0, 0};
    }
    return color;
}

void opcontrol() {
    if (intake_distance.get_object_velocity() > 0) {
        std::vector<double> color = get_color();
        leds::pulse(color, 0);
    } else if (intake_distance.get_object_velocity() < 0) {
        std::vector<double> color = get_color();
        leds::pulse(color, 1);
    }
}

}  // namespace sensors