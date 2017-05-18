//
// Created by antosha on 18.05.17.
//

#include "Airport.h"

Airport::Airport(unsigned airstrip_num): airstrips_num(airstrip_num), airstrips(airstrip_num) {}

int Airport::get_free_airstrip() {
    for (int i = 0; i < airstrips_num; ++i) {
        if(airstrips[i].try_lock())
            return i;
    }
    return -1;
}

void Airport::free_airstrip(unsigned airstrip_num) {
    if(airstrip_num <= airstrips_num )
        airstrips[airstrip_num].unlock();
}

