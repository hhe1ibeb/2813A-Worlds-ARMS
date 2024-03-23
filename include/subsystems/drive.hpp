#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "main.h"

namespace drive {
extern pros::Controller master;
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
void opcontrol(bool curves);
}  // namespace drive

#endif