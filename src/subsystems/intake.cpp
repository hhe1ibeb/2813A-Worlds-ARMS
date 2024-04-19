#include "main.h"

namespace intake {
pros::Motor intake_1(15);
pros::Motor intake_2(-20);

pros::MotorGroup intake({intake_1, intake_2});

void init() {
    intake.set_gearing(MOTOR_GEARSET_06);
    intake.set_brake_modes(MOTOR_BRAKE_COAST);
    intake.set_encoder_units(MOTOR_ENCODER_DEGREES);
    printf("Intake finished initialize\n");
}

void move(int speed) { intake.move_velocity(speed); }

bool is_on = false;

void opcontrol() {
    static int speed = 0;

    if (drive::master.get_digital(DIGITAL_R1)) {
        speed = 600;
    } else if (drive::master.get_digital(DIGITAL_R2)) {
        speed = -600;
    } else
        speed = 0;
    move(speed);
}
}  // namespace intake