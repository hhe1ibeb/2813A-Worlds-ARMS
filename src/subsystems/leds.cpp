#include "main.h"

namespace leds {
void opcontrol() {
    // Create an addrled object
    auto addrled = sylib::Addrled(22, 1, 64);

    // Set the LED strip to a gradient in HSV color space
    // that displays a full range of hues
    addrled.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);

    // Cycle the colors at speed 10
    addrled.cycle(*addrled, 10);
}
}  // namespace leds