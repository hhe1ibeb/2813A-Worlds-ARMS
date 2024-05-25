#ifndef _LEDS_H_
#define _LEDS_H_

#include "main.h"

namespace leds {
extern sylib::Addrled myLights;
void disabled();
void disabled_cycle();
void auton_set();
void auton_cycle();
void set();
void cycle();
void pulse();
void pulse(std::vector<double> color, bool direction);
}  // namespace leds

#endif