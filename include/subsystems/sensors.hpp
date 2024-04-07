#ifndef _SENSORS_H_
#define _SENSORS_H_

#include "main.h"

namespace sensors {

extern pros::Optical intake_optical;
std::vector<double> get_color();
void opcontrol();

}  // namespace sensors

#endif