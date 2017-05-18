//
// Created by antosha on 18.05.17.
//

#ifndef CHUKANOVA2_0_AIRPORT_H
#define CHUKANOVA2_0_AIRPORT_H

#include <iostream>
#include <vector>
#include <mutex>

using std::vector;
using std::cout;
using std::mutex;
using std::endl;

class Airport {
private:
    unsigned airstrips_num;
    vector<mutex> airstrips;
public:
    Airport(unsigned = 2);
    int get_free_airstrip();
    void free_airstrip(unsigned airstrip_num);
};


#endif //CHUKANOVA2_0_AIRPORT_H
