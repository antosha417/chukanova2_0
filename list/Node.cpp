//
// Created by Nikitos
//

#include "Node.h"

Node::Node(int value_, Node* next_){
    value = value_;
    next = next_;
}

Node::Node(){
    next = this;
}

Node::Node(int value_){
    value = value_;
    next = this;
}

Node::~Node(){
    next = nullptr;
}

Node* Node::get_next(){
    return next;
}


void Node::set_next(Node* next_){
    next = next_;
}

int Node::get_value(){
    return value;
}

void Node::set_value(int value_){
    value = value_;
}