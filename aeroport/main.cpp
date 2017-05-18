//
// Created by antosha on 18.05.17.
//


#include <iostream>
#include <unistd.h>
#include <thread>

#include "Airctaft.h"

using std::thread;
using std::pair;


int main(){
    Airport airport;
    vector<pair<Aircraft*, thread>> planes;

    unsigned aircraft_landing_num = 500;
    unsigned aircraft_takeoff_num = 600;

    for (int i = 0; i < 1000; ++i) {
        sleep(1);
        if(!(rand()%aircraft_landing_num)) {
            Aircraft* plane = new Aircraft(airport);
            planes.push_back(pair<Aircraft*, thread>(plane, thread([plane](){plane->land();})));
        }
        if(!(rand()%aircraft_takeoff_num)) {
            Aircraft* plane = new Aircraft(airport);
            planes.push_back(pair<Aircraft*, thread>(plane, thread([plane](){plane->takeoff();})));
        }
    }

    while(!planes.empty()){
        planes.back().second.join();
        delete planes.back().first;
        planes.pop_back();
    }

    return 0;
}



