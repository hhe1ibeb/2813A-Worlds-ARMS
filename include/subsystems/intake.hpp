#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "main.h"

namespace intake {

extern pros::MotorGroup intake;
extern pros::ADIDigitalOut intake_piston;
void init();
void move(int speed);
void opcontrol();

}  // namespace intake

#endif