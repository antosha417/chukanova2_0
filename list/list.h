//
// Created by antosha on 15.03.17.
//

#ifndef CHUKANOVA2_0_LIST_H
#define CHUKANOVA2_0_LIST_H


#include "Node.h"

class list {
private:
    unsigned len;
public:
    Node* head;

    list();
    ~list();

    unsigned get_len();

    void add_to_num(unsigned, int);
    void delete_from_num(int);

    void dump();
};


#endif //CHUKANOVA2_0_LIST_H
