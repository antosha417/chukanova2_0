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
    Airport airport; // Создаём аэропорт.
    vector<pair<Aircraft*, thread>> planes; // Вектор в коротом будем зранить пары <самолёт, поток в котором он взлетает или садится>

    unsigned aircraft_landing_num = 500; // с вероятностью 1/aircraft_landing_num каждую секунду появляется самолёт на посадку
    unsigned aircraft_takeoff_num = 600; // с вероятностью 1/aircraft_takeoff_num каждую секунду появляется самолёт на посадку

    for (int i = 0; i < 1000; ++i) {
        sleep(1);
        if(!(rand()%aircraft_landing_num)) { // Если случайноечисло от 0 до aircraft_landing_num 0, то
            Aircraft* plane = new Aircraft(airport); // Создaём самолёт
            planes.push_back(pair<Aircraft*, thread>(plane, thread([plane](){plane->land();}))); // создаём поток и вызываем у самолёта функцию land()
        }
        if(!(rand()%aircraft_takeoff_num)) { // Если случайноечисло от 0 до aircraft_takeoff_num 0, то
            Aircraft* plane = new Aircraft(airport); // Создaём самолёт
            planes.push_back(pair<Aircraft*, thread>(plane, thread([plane](){plane->takeoff();}))); // создаём поток и вызываем у самолёта функцию takeoff()
        }
    }

    while(!planes.empty()){ // пока не удалили все самолёты
        planes.back().second.join(); // ждём пока самолёт закончит работу
        delete planes.back().first; // чистим память
        planes.pop_back(); // удвляем самолёт из вектора
    }

    return 0;
}



