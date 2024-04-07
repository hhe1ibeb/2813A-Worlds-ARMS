#include "main.h"

#include "ARMS/config.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    arms::init();
    sylib::initialize();

    // subsystems
    drive::init();
    screen::init();
    intake::init();
    wings::init();
    leds::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous();

void odom_tuning(int mode);
void pid_tuning(int mode);

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    while (true) {
        drive::opcontrol(false);
        intake::opcontrol();
        wings::opcontrol();
        screen::odom_debug();
        sensors::opcontrol();

        // autonomous tests
        if (!pros::competition::is_connected() &&
            drive::master.get_digital_new_press(DIGITAL_Y)) {
            autonomous();
        }
        if (!pros::competition::is_connected() &&
            drive::master.get_digital(DIGITAL_UP)) {
            odom_tuning(1);  // 1 = tpi, 2 = track width, 3 = middle distance
        }
        if (!pros::competition::is_connected() &&
            drive::master.get_digital(DIGITAL_DOWN)) {
            pid_tuning(1);  // 1 = angular, 2 = linear, 3 = boomerang
        }
        pros::delay(10);
    }
}
