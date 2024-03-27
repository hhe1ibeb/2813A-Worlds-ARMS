#ifndef _WINGS_H_
#define _WINGS_H_

#include "main.h"

namespace wings {

extern pros::ADIDigitalOut left_front_wing;
extern pros::ADIDigitalOut right_front_wing;
extern pros::ADIDigitalOut left_back_wing;
extern pros::ADIDigitalOut right_back_wing;

void init();
void front_wings(bool state);
void back_wings(bool state);
void opcontrol();

}  // namespace wings

#endif