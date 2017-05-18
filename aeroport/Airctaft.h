//
// Created by antosha on 18.05.17.
//

#ifndef CHUKANOVA2_0_AIRCTAFT_H
#define CHUKANOVA2_0_AIRCTAFT_H

#include "Airport.h"

using std::string;

class Aircraft {
private:
    unsigned landing_time;
    unsigned takeoff_time;
    Airport& airport;
    string name;

    string gen_name();
    int wait_for_airstrip();
public:
    Aircraft(Airport&, unsigned = 3, unsigned = 3);
    void land();
    void takeoff();
};


#endif //CHUKANOVA2_0_AIRCTAFT_H
