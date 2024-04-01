#include "main.h"

double calculate_curves(double x, double t) {
    double y =
        (exp(-t / 10.0) + exp((abs(x) - 127) / 10.0) * (1 - exp(-t / 10.0))) *
        x;

    return y;
}

void drive_curves_arcade(double forward, double turn) {
    const double forward_t = 4.3;
    const double turn_t = 2.1;

    double forward_curve = calculate_curves(forward, forward_t);
    double turn_curve = calculate_curves(turn, turn_t);

    double left = forward_curve + turn_curve;
    double right = forward_curve - turn_curve;

    drive::left_motors.move_velocity(left);
    drive::right_motors.move_velocity(right);
}

namespace drive {
pros::Motor L1 = pros::Motor(-13, pros::E_MOTOR_GEARSET_06);
pros::Motor L2 = pros::Motor(-14, pros::E_MOTOR_GEARSET_06);
pros::Motor L3 = pros::Motor(-16, pros::E_MOTOR_GEARSET_06);
pros::Motor R1 = pros::Motor(15, pros::E_MOTOR_GEARSET_06);
pros::Motor R2 = pros::Motor(17, pros::E_MOTOR_GEARSET_06);
pros::Motor R3 = pros::Motor(18, pros::E_MOTOR_GEARSET_06);

pros::MotorGroup left_motors({L1, L2, L3});
pros::MotorGroup right_motors({R1, R2, R3});

pros::IMU imu_sensor(14);

pros::Controller master(pros::E_CONTROLLER_MASTER);

void drive_imu_display_loading(int iter) {
    // If the lcd is already initialized, don't run this function
    if (pros::lcd::is_initialized()) return;

    // Boarder
    int boarder = 50;

    // Create the boarder
    pros::screen::set_pen(COLOR_WHITE);
    for (int i = 1; i < 3; i++) {
        pros::screen::draw_rect(boarder + i, boarder + i, 480 - boarder - i,
                                240 - boarder - i);
    }

    // While IMU is loading
    if (iter < 2000) {
        static int last_x1 = boarder;
        pros::screen::set_pen(0x00FF6EC7);  // EZ Pink
        int x1 = (iter * ((480 - (boarder * 2)) / 2000.0)) + boarder;
        pros::screen::fill_rect(last_x1, boarder, x1, 240 - boarder);
        last_x1 = x1;
    }
    // Failsafe time
    else {
        static int last_x1 = boarder;
        pros::screen::set_pen(COLOR_RED);
        int x1 = ((iter - 2000) * ((480 - (boarder * 2)) / 1000.0)) + boarder;
        pros::screen::fill_rect(last_x1, boarder, x1, 240 - boarder);
        last_x1 = x1;
    }
}

bool drive_imu_calibrate(bool run_loading_animation) {
    imu_sensor.reset();
    int iter = 0;
    while (true) {
        iter += utils::DELAY_TIME;

        if (run_loading_animation) drive_imu_display_loading(iter);

        if (iter >= 2000) {
            if (!(imu_sensor.get_status() &
                  pros::c::E_IMU_STATUS_CALIBRATING)) {
                break;
            }
            if (iter >= 3000) {
                printf("No IMU plugged in, (took %d ms to realize that)\n",
                       iter);
                return false;
            }
        }
        pros::delay(utils::DELAY_TIME);
    }
    printf("IMU is done calibrating (took %d ms)\n", iter);
    return true;
}

void init() { drive_imu_calibrate(true); }

void opcontrol(bool curves) {
    switch (curves) {
        case true:
            drive_curves_arcade(master.get_analog(ANALOG_LEFT_Y),
                                master.get_analog(ANALOG_RIGHT_X));
            break;
        case false:
            arms::chassis::arcade(master.get_analog(ANALOG_LEFT_Y),
                                  master.get_analog(ANALOG_RIGHT_X));
            break;
    }
    arms::chassis::arcade(master.get_analog(ANALOG_LEFT_Y),
                          master.get_analog(ANALOG_RIGHT_X));
}
}  // namespace drive