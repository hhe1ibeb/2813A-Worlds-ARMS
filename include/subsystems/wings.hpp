#ifndef _WINGS_H_
#define _WINGS_H_

#include "main.h"

namespace wings {

extern pros::ADIDigitalOut left_front_wing;
extern pros::ADIDigitalOut right_front_wing;
extern pros::ADIDigitalOut left_back_wing;
extern pros::ADIDigitalOut right_back_wing;

extern pros::ADIDigitalOut pto;

void init();
void front(bool state);
void back(bool state);
void front(bool right, bool left);
void back(bool right, bool left);
void opcontrol();

}  // namespace wings

#endif