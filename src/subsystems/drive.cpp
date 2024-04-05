#include "main.h"
#define FORWARD_T 4.3
#define TURN_T 2.1

namespace drive {
pros::IMU imu_sensor(14);

pros::Controller master(pros::E_CONTROLLER_MASTER);

double calculate_curves(double x, double t) {
    double y =
        (exp(-t / 10.0) + exp((abs(x) - 127) / 10.0) * (1 - exp(-t / 10.0))) *
        x;

    return y;
}

double drive_curves_arcade_forward(double forward, double forward_t) {
    double forward_curve = calculate_curves(forward, forward_t);

    return forward_curve;
}

double drive_curves_arcade_turn(double turn, double turn_t) {
    double turn_curve = calculate_curves(turn, turn_t);

    return turn_curve;
}

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
        pros::screen::set_pen(COLOR_LIME);
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
            arms::chassis::arcade(
                drive_curves_arcade_forward(master.get_analog(ANALOG_LEFT_Y),
                                            FORWARD_T),
                drive_curves_arcade_turn(master.get_analog(ANALOG_RIGHT_X),
                                         TURN_T));
            break;
        case false:
            arms::chassis::arcade(master.get_analog(ANALOG_LEFT_Y),
                                  master.get_analog(ANALOG_RIGHT_X));
            break;
    }
}
}  // namespace drive