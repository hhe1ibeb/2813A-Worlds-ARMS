#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include "main.h"

namespace shooter {

extern pros::Motor shooter;
void move(double velocity);
void opcontrol();

}  // namespace shooter

#endif