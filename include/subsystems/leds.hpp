#ifndef _LEDS_H_
#define _LEDS_H_

#include "main.h"

namespace leds {
extern sylib::Addrled myLights;
void init();
void disabled();
void gradient();
void cycle();
void rotate();
void pulse();
void pulse(std::vector<double> color, bool direction);
}  // namespace leds

#endif