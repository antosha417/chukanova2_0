//
// Created by antosha on 15.03.17.
//

#ifndef CHUKANOVA2_0_NODE_H
#define CHUKANOVA2_0_NODE_H


class Node {
private:
    Node* next;
    int value;
public:
    Node(int, Node*);
    Node(int);
    Node();
    ~Node();
    Node* get_next();
    void set_next(Node*);

    int get_value();
    void set_value(int);
};


#endif //CHUKANOVA2_0_NODE_H
