#include "main.h"

namespace leds {

// sylib::Addrled left(22, 1, 10);
// sylib::Addrled right(22, 2, 10);

sylib::Addrled myLights(22, 2, 20);

const int CHASSIS_COLOR_START = 0xD8EBFF;
const int CHASSIS_COLOR_END = 0x004589;

void disabled() {}
void init() { myLights.gradient(CHASSIS_COLOR_START, CHASSIS_COLOR_END); }
void gradient() { myLights.gradient(0x00FF00, 0x0000FF); }
void cycle() { myLights.cycle(*myLights, 15); }
void rotate() { myLights.rotate(1, false); }

void pulse() { myLights.pulse(0xFF36FF, 2, 10); }

void pulse(std::vector<double> color, bool direction) {
    myLights.pulse(sylib::Addrled::rgb_to_hex(color[0], color[1], color[2]), 2,
                   10, 0, direction);
}
}  // namespace leds