#include "main.h"

void near_qual() {}

void far_qual() {}

void near_elim() {}

void far_elim() {}

void skills() {}

void odom_tuning(int mode) {  // 0 = tpi, 1 = track width, 2 = middle distance
    arms::odom::reset();
    switch (mode) {
        case 0:  // repeat until X position matches distance pushed
            int forward_distance = 24;
            arms::chassis::move(forward_distance, 100);
            printf("X: %f\n", arms::odom::getPosition().x);
            printf("New TPI should be: %f\n",
                   TPI * arms::odom::getPosition().x / forward_distance);
            break;
        case 1:  // for motor encoders, remember to disable imu, repeat until
                 // heading matches the degrees turned
            int degrees = 135;
            arms::chassis::turn(degrees, 100);
            printf("Heading: %f\n", arms::odom::getHeading());
            printf("New track widtu should be: %f\n",
                   TRACK_WIDTH * arms::odom::getHeading() / degrees);
            break;
        case 2:  // repeat until Y position after turn is close to 0
            arms::chassis::turn(90, 100);
            printf("Y: %f\n", arms::odom::getPosition().y);
            printf("Heading: %f\n", arms::odom::getHeading());
            printf("New middle distance should be: %f\n",
                   MIDDLE_DISTANCE + (arms::odom::getPosition().y /
                                      (arms::odom::getHeading() * M_PI / 180)));
            break;
    }
}

void pid_tuning(int mode) {  // 0 = angular, 1 = linear, 2 = boomerang
    switch (mode) {
        arms::odom::reset({0, 0}, 0);
        case 0:  // once done, remove ASYNC flag and delay to check
            arms::chassis::turn(90, arms::ASYNC);
            pros::delay(3000);
            break;
        case 1:
            arms::chassis::move(24, arms::ASYNC);
            pros::delay(3000);
            break;
        case 2:
            arms::chassis::move(
                {24, 24,
                 90});  // Increase TRACKING_KP if the robot doesn't reach the
                        // target point and decrease it if the robot starts
                        // oscillating too much. Increase LEAD_PCT to make
                        // boomerang more aggressive and decrease it to make
                        // boomerang less aggressive.
    }
}

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