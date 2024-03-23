#ifndef _WINGS_H_
#define _WINGS_H_

#include "main.h"

namespace wings {

extern pros::ADIAnalogOut left_front_wing;
extern pros::ADIAnalogOut right_front_wing;
extern pros::ADIAnalogOut left_back_wing;
extern pros::ADIAnalogOut right_back_wing;

void init();
void front_wings(bool state);
void back_wings(bool state);
void opcontrol();

}  // namespace wings

#endif