#include "ARMS/config.h"
#include "main.h"

const int intake_length = 12;  // in inches

void odom_tuning(int mode) {  // 1 = tpi, 2 = track width, 3 = middle distance
    arms::odom::reset();
    arms::chassis::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    int forward_distance = 24;
    int degrees = 180;
    switch (mode) {
        case 1:  // repeat until X position matches distance pushed
            arms::chassis::move(forward_distance, 100);
            pros::delay(1000);
            printf("X: %f\n", arms::odom::getPosition().x);
            printf("New TPI should be: %f\n",
                   TPI * forward_distance / arms::odom::getPosition().x);
            break;
        case 2:  // for motor encoders, remember to disable imu, repeat until
                 // heading matches the degrees turned
            arms::chassis::turn(degrees, 100, arms::THRU);
            pros::delay(1000);
            printf("Heading: %f\n", arms::odom::getHeading());
            printf("New track width should be: %f\n",
                   TRACK_WIDTH * arms::odom::getHeading() / degrees);
            break;
        case 3:  // repeat until Y position after turn is close to 0
            arms::chassis::turn(90, 100);
            pros::delay(1000);
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
    arms::chassis::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    switch (mode) {
        case 1:  // once done, remove ASYNC flag and delay to check
            arms::chassis::turn(90);
            // pros::delay(3000);
            break;  // Increase kP until the robot oscillates around the target.
                    // Increase kD until the robot no longer overshoots the
                    // target. If the robot is still a little bit off from the
                    // target, increase kI until this no longer happens.
        case 2:
            arms::chassis::move(24);
            // pros::delay(3000);
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

void near_qual() {
    arms::odom::reset({0, 0}, -135);
    // push preload with back
    arms::chassis::move({26, 10, -180}, 100, arms::REVERSE);
    // turn and push out match load
    arms::chassis::move(5, 100);
    arms::chassis::turn(0, 100);
    arms::odom::reset({0, 0}, -180);
    arms::chassis::move({20, 8, -90}, 100, arms::REVERSE | arms::ASYNC);
    pros::delay(300);
    wings::back(true);
    arms::chassis::waitUntilFinished(0.5);
    wings::back(0, 0);
    arms::chassis::move({24, 16, -90}, 100, arms::REVERSE);
    // push to side and touch bar
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move({-40, 0, 0}, 100, arms::REVERSE | arms::ASYNC);
    pros::delay(1000);
    wings::back(1, 0);
}

void far_qual_with_bar() {
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(40, 100, arms::ASYNC);
    wings::back(1, 0);
    pros::delay(100);
    wings::back(false);
    intake::move(200);
    arms::chassis::waitUntilFinished(0);
    arms::chassis::turn(-80, 100);
    intake::move(-600);
    pros::delay(600);
    arms::chassis::turn(110, 100);
    arms::odom::reset({0, 0}, 0);
    intake::move(300);
    arms::chassis::move(26, 100);
    arms::chassis::turn(-160, 100);
    intake::move(-300);
    pros::delay(500);
    intake::move(300);
    arms::chassis::turn(-70, 100);
    arms::chassis::move(20, 100);
    arms::chassis::turn(-180, 100);
    wings::front(true);
    arms::odom::reset({0, 0}, 0);
    intake::move(-300);
    arms::chassis::move(36, 100);
    arms::odom::reset({0, 0}, 0);
    intake::move(0);
    arms::chassis::move(-24, 100, arms::REVERSE);
    wings::front(false);
    arms::chassis::turn(90, 100);
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(-46, 100, arms::REVERSE);
    arms::chassis::turn(-90, 100);
    arms::odom::reset({0, 0}, 0);
    wings::back(1, 0);
    arms::chassis::move(-10, 100, arms::REVERSE);
}

void far_qual_no_bar() {
    // fetch ball under bar
    arms::odom::reset({0, 0}, 0);
    intake::move(300);
    wings::back(1, 0);
    pros::delay(500);
    arms::chassis::move(10, 60);
    wings::back(false);
    // push ball from matchload zone
    arms::chassis::move({-24, 0, 0}, 100, arms::REVERSE);
    arms::chassis::move({-40, -16, 100}, 60, arms::REVERSE | arms::ASYNC);
    wings::back(0, 1);
    arms::chassis::waitUntilFinished(0);
    intake::move(0);
    wings::back(0, 0);
    // push ball to goal
    arms::chassis::turn(240, 100);
    intake::move(-300);
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move({18, 0}, 100);
    arms::chassis::move({12, 0}, 100, arms::REVERSE);
    arms::chassis::move({18, 0}, 100);
    arms::odom::reset({0, 0}, 0);
    // step back
    arms::chassis::move(-24, 100, arms::REVERSE);
    arms::chassis::turn(30, 100);
    arms::odom::reset({0, 0}, 0);
    // fetch middle ball
    intake::move(300);
    arms::chassis::move({32, 44, 90}, 100);
    arms::chassis::turn(-60, 100, arms::ASYNC);
    intake::move(-300);
    arms::chassis::waitUntilFinished(0);
    // fetch middle triball and push three in
    intake::move(300);
    arms::chassis::turn(45, 100);
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(16, 60);
    arms::chassis::turn(-135, 100, arms::RELATIVE);
    arms::odom::reset({0, 0}, 0);
    intake::move(-300);
    wings::front(true);
    arms::chassis::move(24, 100);
    // bump again
    arms::chassis::move({12, 0}, 100, arms::REVERSE);
    arms::chassis::move(24, 100);
    arms::odom::reset({0, 0}, 0);
    wings::front(false);
    // touch bar
    arms::chassis::turn(90, 100);
    intake::move(0);
    arms::chassis::move({-20, -36}, 100, arms::REVERSE);
    arms::chassis::move({-40, -40, 0}, arms::REVERSE);
    wings::back(1, 0);
}

void near_elim() {
    intake::move(300);
    arms::odom::reset({0, 0}, 0);
    // steal middle triball
    arms::chassis::move({48, -8, 0}, 100, arms::ASYNC);
    pros::delay(500);
    wings::back(1, 0);
    pros::delay(250);
    wings::back(false);
    arms::chassis::waitUntilFinished(0);
    // push middle triball
    arms::chassis::turn(-80, 100);
    arms::odom::reset({0, 0}, 0);
    intake::move(-600);
    wings::front(0, 1);
    arms::chassis::move(20, 100);
    // return to matchload bar
    arms::chassis::turn(45, 100);
    arms::odom::reset({0, 0}, 0);
    wings::front(false);
    intake::move(0);
    arms::chassis::move(-66, 100, arms::REVERSE);
    arms::chassis::turn(90, 100);
    // push preload in match load zone
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(12, 100);
    wings::back(0, 1);
    arms::chassis::move(-22, 100, arms::REVERSE);
    // push two balls to offensive zone
    arms::chassis::turn(45, 100);
    wings::back(false);
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(-40, 100, arms::REVERSE);
    arms::chassis::move({22, -22, 150}, 100);
}

void far_elim() {  // not fully tested!!
    arms::odom::reset({0, 0}, 0);
    pros::delay(300);
    intake::move(300);
    // rush fetch middle triball
    arms::chassis::move({48, 28, 45}, 100, arms::ASYNC);
    wings::back(1, 0);
    pros::delay(500);
    wings::back(false);
    arms::chassis::move({-15, 0, 0}, 100, arms::REVERSE);
    intake::move(-300);
    arms::chassis::turn(-45, 100);
    // triball under bar
    arms::chassis::turn(100, 100);
    arms::odom::reset({0, 0}, 0);
    intake::move(300);
    arms::chassis::move(30, 100);
    arms::odom::reset({0, 0}, 0);
    // hook out triball in match load zone
    arms::chassis::move({-40, 0, 0}, 100, arms::REVERSE);
    intake::move(0);
    wings::back(0, 1);
    arms::chassis::move({-54, -16, 100}, 60, arms::REVERSE);
    wings::back(false);
    // push them in goal with back
    arms::chassis::turn(70, 100);
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(-16, 100, arms::REVERSE);
    // turn to middle ball
    arms::chassis::move({0, 0}, 100);
    arms::chassis::turn(-100, 100);
    // hit them in with wings
    arms::chassis::move(48, 100);
    wings::front(0, 1);
    arms::chassis::turn(-230, 100);
    arms::odom::reset({0, 0}, 0);
    intake::move(-300);
    arms::chassis::move(36, 100);
    arms::chassis::move({24, 0}, 0);
    intake::move(0);
}

void skills() {}

void autonomous() {
    arms::chassis::setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    leds::auton_set();
    leds::auton_cycle();
    switch (arms::selector::auton) {
        case 1:
            near_qual();
            break;
        case 2:
            far_qual_with_bar();
            break;
        case 3:
            far_qual_no_bar();
        case 4:
            near_elim();
            break;
        case 5:
            far_elim();
            break;
        case 0:
            skills();
            break;
    }
}