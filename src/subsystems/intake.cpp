#include "main.h"

namespace intake {
pros::Motor intake_1(-5);
pros::Motor intake_2(6);

pros::MotorGroup intake({intake_1, intake_2});

void init() {
    intake.set_gearing(MOTOR_GEARSET_06);
    intake.set_brake_modes(MOTOR_BRAKE_COAST);
    intake.set_encoder_units(MOTOR_ENCODER_DEGREES);
}

void move(int speed) { intake.move_velocity(speed); }

void opcontrol() {
    static int speed = 0;

    if (drive::master.get_digital(DIGITAL_R1))
        speed = 100;
    else if (drive::master.get_digital(DIGITAL_R2))
        speed = -100;
    else
        speed = 0;

    move(speed);
}
}  // namespace intake