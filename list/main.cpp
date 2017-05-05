//
// Created by Nikitos
//


#include <iostream>
#include "list.h"

int main(){

    list* a = new list();

    std::cout<<a->get_len()<<' '<<a->head<<' '<<a->head->get_next()<<std::endl;

    a->dump();

    a->add_to_num(0, 12);
    a->add_to_num(a->get_len()-1, 1);
    a->add_to_num(a->get_len()-1, 16);
    a->add_to_num(a->get_len()-1, 15);
    a->add_to_num(a->get_len()-1, -25);

    a->dump();

    a->delete_from_num(a->get_len());

    a->dump();

    a->delete_from_num(0);

    a->dump();

    std::cout<<"Let's play!"<<std::endl;

    a->add_to_num(a->get_len()-1, 17);
    a->add_to_num(a->get_len()-1, 18);
    a->add_to_num(a->get_len()-1, -50);
    a->add_to_num(a->get_len()-1, -60);

    a->dump();

    a->counter(3);

    return 0;
}