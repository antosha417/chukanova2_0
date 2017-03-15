//
// Created by antosha on 15.03.17.
//

#include <assert.h>
#include <iostream>
#include "list.h"


unsigned list::get_len(){
    return len;
}

list::list(){
    head = new Node();
    len = 0;
}

list::~list(){
    for(unsigned i = len - 1; i > 0; --i){
        delete_from_num(i);
    }
    head = nullptr;
}

void list::add_to_num(unsigned num, int value){
    assert(len >= num);
    Node* current = head->get_next();
    for(unsigned i = 0; i < num; i++){
        current = current->get_next();
    }
    current->set_next(new Node(value, current->get_next()));
    ++len;
}

void list::delete_from_num(int num){
    assert(len > 0);
    num %= len;
    Node *current = head->get_next();

    for (unsigned i = 0; i < num; i++) {
        current = current->get_next();
    }
    Node *temp = current->get_next();
    if(temp == head) {
        temp = head->get_next();
        current = head;
    }
    current->set_next(temp->get_next());
    delete temp;

    --len;
}

void list::dump(){
    Node* current = head->get_next();

    std::cout<<"<Class list: len="<<len<<"| [ ";

    if(len > 0) {
        for(unsigned i = 0; i < len - 1; i++){
            std::cout<<current->get_value()<<", ";
            current = current->get_next();
        }
        std::cout<<current->get_value();
    }
    std::cout<<" ]>";

    std::cout<<std::endl;
}