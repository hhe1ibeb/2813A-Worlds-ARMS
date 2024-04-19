#include "main.h"

namespace screen {

void init() {
    pros::lcd::initialize();
    lv_color_t black = LV_COLOR_MAKE(0, 0, 0);
    lv_color_t white = LV_COLOR_MAKE(255, 255, 255);
    pros::lcd::set_background_color(black);
    pros::lcd::set_text_color(white);
}

void print_2813A() {
    pros::lcd::print(0, "  ___   ___  __ ____  ");
    pros::lcd::print(1, " |__ \\ / _ \\/_ |___ \\   /\\ ");
    pros::lcd::print(2, "    ) | (_) || | __) | /  \\ ");
    pros::lcd::print(3, "   / / > _ < | ||__ < / /  \\ ");
    pros::lcd::print(4, "  / /_| (_) || |___) / ____ \\ ");
    pros::lcd::print(5, " |____|\\___/ |_|____/_/    \\_\\");
}

void print_capy() {
    pros::lcd::print(0, "  ___   _   ___   ___");
    pros::lcd::print(1, " / __\\ /_\\ / _ \\/\\_\\");
    pros::lcd::print(2, "/ /  //_\\\\/ /_)/_ _\\/");
    pros::lcd::print(3, "/ /__/  _  \\/ __/ / \\");
    pros::lcd::print(4, "\\____\\_/ \\_/\\/   \\_/");
}

void print_position() {
    pros::lcd::print(0, "X: %f", arms::odom::getPosition().x);
    pros::lcd::print(1, "Y: %f", arms::odom::getPosition().y);
    pros::lcd::print(2, "H: %f", arms::odom::getHeading());
}

void odom_debug() {
    pros::lcd::set_text(0, "X: " + std::to_string(arms::odom::getPosition().x));
    pros::lcd::set_text(1, "Y: " + std::to_string(arms::odom::getPosition().y));
    pros::lcd::set_text(2, "H: " + std::to_string(arms::odom::getHeading()));
    pros::lcd::set_text(
        3, "Left: " + std::to_string(arms::odom::getLeftEncoder()));
    pros::lcd::set_text(
        4, "Right: " + std::to_string(arms::odom::getRightEncoder()));
    pros::lcd::set_text(
        5, "Middle: " + std::to_string(arms::odom::getMiddleEncoder()));
    pros::lcd::set_text(
        6, "Inertial: " + std::to_string(drive::imu_sensor.get_rotation()));
}
}  // namespace screen