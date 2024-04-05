#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "main.h"

namespace intake {

extern pros::MotorGroup intake;
void init();
void move(int speed);
void opcontrol();

}  // namespace intake

#endif