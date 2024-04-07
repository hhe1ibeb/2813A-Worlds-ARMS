#include "main.h"

const int intake_length = 12;  // in inches

void odom_tuning(int mode) {  // 1 = tpi, 2 = track width, 3 = middle distance
    arms::odom::reset();
    int forward_distance = 24;
    int degrees = 135;
    switch (mode) {
        case 1:  // repeat until X position matches distance pushed
            arms::chassis::move(forward_distance, 100);
            printf("X: %f\n", arms::odom::getPosition().x);
            printf("New TPI should be: %f\n",
                   TPI * arms::odom::getPosition().x / forward_distance);
            break;
        case 2:  // for motor encoders, remember to disable imu, repeat until
                 // heading matches the degrees turned
            arms::chassis::turn(degrees, 100);
            printf("Heading: %f\n", arms::odom::getHeading());
            printf("New track widtu should be: %f\n",
                   TRACK_WIDTH * arms::odom::getHeading() / degrees);
            break;
        case 3:  // repeat until Y position after turn is close to 0
            arms::chassis::turn(90, 100);
            printf("Y: %f\n", arms::odom::getPosition().y);
            printf("Heading: %f\n", arms::odom::getHeading());
            printf("New middle distance should be: %f\n",
                   MIDDLE_DISTANCE + (arms::odom::getPosition().y /
                                      (arms::odom::getHeading() * M_PI / 180)));
            break;
    }
}

void pid_tuning(int mode) {  // 1 = angular, 2 = linear, 3 = boomerang
    arms::odom::reset({0, 0}, 0);
    switch (mode) {
        case 1:  // once done, remove ASYNC flag and delay to check
            arms::chassis::turn(90, arms::ASYNC);
            pros::delay(3000);
            break;
        case 2:
            arms::chassis::move(24, arms::ASYNC);
            pros::delay(3000);
            break;
        case 3:
            arms::chassis::move(
                {24, 24,
                 90});  // Increase TRACKING_KP if the robot doesn't reach the
                        // target point and decrease it if the robot starts
                        // oscillating too much. Increase LEAD_PCT to make
                        // boomerang more aggressive and decrease it to make
                        // boomerang less aggressive.
    }
}

double get_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void intake_ball_at(std::vector<double> target, int speed, int intake_speed,
                    bool pid = 1) {
    intake::move(intake_speed);
    if (pid)
        arms::chassis::move(target, speed, intake_length, arms::ASYNC);
    else
        arms::chassis::move(target, speed, intake_length,
                            arms::ASYNC | arms::THRU);
}

void near_qual() {}

void far_qual() {}

void near_elim() {}

void far_elim() {}

void skills() {}

void autonomous() {
    switch (arms::selector::auton) {
        case 1:
            near_qual();
            break;
        case 2:
            far_qual();
            break;
        case 3:
            near_elim();
            break;
        case 4:
            far_elim();
            break;
        case 0:
            skills();
            break;
    }
}