#include "main.h"

void near_qual() {}

void far_qual() {}

void near_elim() {}

void far_elim() {}

void skills() {}

void tuning() {
    arms::odom::reset({0, 0}, 0);
    arms::chassis::move(24, 100);
}

void autonomous() {
    tuning();
    // switch (arms::selector::auton) {
    //     case 1:
    //         near_qual();  // runs red side autonomous 1 code
    //         break;
    //     case 2:
    //         near_elim();  // runs red side autonomous 2 code
    //         break;
    //     case -1:
    //         far_qual();  // runs blue side autonomous 1 code
    //         break;
    //     case -2:
    //         far_elim();  // runs blue side autonomous 2 code
    //         break;
    //     case 0:
    //         skills();  // runs skills autonomous code
    //         break;
    // }
}