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
    unsigned airstrips_num;  // количество взлётнопосадчных полос
    vector<mutex> airstrips; // мютексы на полосы
public:
    Airport(unsigned = 2); // конструктор принамает количество полос
    int get_free_airstrip(); // возвращает номер свободной полосы и помечает её как занятую, или -1
    void free_airstrip(unsigned airstrip_num); // освобождает полосу
};


#endif //CHUKANOVA2_0_AIRPORT_H
