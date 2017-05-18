//
// Created by antosha on 18.05.17.
//

#include <unistd.h>
#include "Airctaft.h"

Aircraft::Aircraft(Airport& airport, unsigned takeoff_time, unsigned landing_time):
        takeoff_time(takeoff_time),
        landing_time(landing_time),
        airport(airport){
    name = gen_name();
    cout<<name + " appeared."<<std::endl;
}

int Aircraft::wait_for_airstrip() {
    int airstrip_num = 0;
    while((airstrip_num = airport.get_free_airstrip()) == -1);
    return airstrip_num;
}

void Aircraft::land() {
    int airstrip_num = wait_for_airstrip();
    if(airstrip_num < 0) {
        cout<<"Aircraft flew away from airport :c"<<std::endl;
        return;
    }
    cout<<"Aircraft is lending to "<<airstrip_num<<"'th airstrip."<<std::endl;
    sleep(landing_time);
    airport.free_airstrip((unsigned)airstrip_num);
}

void Aircraft::takeoff() {
    int airstrip_num = wait_for_airstrip();
    if(airstrip_num < 0) {
        cout<<"Aircraft crushed into the wall :c"<<std::endl;
        return;
    }
    cout<<"Aircraft is taking off from "<<airstrip_num<<"'th airstrip."<<std::endl;
    sleep(takeoff_time);
    airport.free_airstrip((unsigned)airstrip_num);
}

string Aircraft::gen_name() {
    vector<string> models = {"Airbus", "Boeing", "ИЛ", "ТУ"};
    return models[rand()%models.size()] + "  " + std::to_string(100 + rand()%899);
}
