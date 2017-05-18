//
// Created by antosha on 18.05.17.
//

#ifndef CHUKANOVA2_0_AIRCTAFT_H
#define CHUKANOVA2_0_AIRCTAFT_H

#include "Airport.h"

using std::string;

class Aircraft {
private:
    unsigned landing_time;  // время на посадку
    unsigned takeoff_time;  // влемя на взлёт
    Airport& airport; // ссылка на аэропорт откуда взлетать или садиться
    string name; // название самолёта

    string gen_name(); // функция возвращает случайное имя для самолёта
    int wait_for_airstrip(); // функция ищёт сводобную полосу, занимает её и возврашает её номер
public:
    Aircraft(Airport&, unsigned = 3, unsigned = 3); // коструктор принимает аэропорт и время посадки и взлёта в секундах(по умелчанию 3)
    void land(); // посадка
    void takeoff(); // взлёт
};


#endif //CHUKANOVA2_0_AIRCTAFT_H
