#ifndef ANTOSHA_TREE_H
#define ANTOSHA_TREE_H

#include <vector>
#include <iostream>

int SHIFT = 0;

template <typename T>
class Node{
 private:
  T elem;
  std::vector<Node*> children;
  static size_t size;

 public:
  Node(T);
  ~Node();
  void insert(T);
  void remove(T);
  std::vector<Node*> getChildren() {
    return children;
  }
  size_t getSize() {
    return size;
  }
  T getKey() {
    return elem;
  }
  Node<T>* find(T);
  void dump();
  T get_elem();
};

template <typename T>
size_t Node<T>::size = 1;

template <typename T>
Node<T>::Node(T _elem) {
  elem = _elem;
}

template <typename T>
Node<T>::~Node() {
  while(children.size() != 0){
    delete children.back();
    children.pop_back();
  }
}


template <typename T>
void Node<T>::insert(T _elem) {
  children.push_back(new Node<T>(_elem));
  size++;
}

template <typename T>
Node<T>* Node<T>::find(T _elem) {
  Node<T>* res = NULL;
  if (elem == _elem) {
    return this;
  } else {
    for(int i = 0; i < children.size(); i++){
      if (res == NULL) {
        res = children[i]->find(_elem);
      } else {
        return res;
      }
    }
  }
  return res;
}

template <typename T>
void Node<T>::dump() {
  for(int i = 0; i < SHIFT; i++){
    std::cout<< '\t';
  }
  std::cout<<elem;
  if (children.size() > 0) {
    int temp = SHIFT;
    SHIFT = 1;
    children[0]->dump();
    if(children.size() > 1)
      SHIFT = temp + 1;
    for (int i = 1; i < children.size(); i++) {
      children[i]->dump();
    }
    SHIFT--;
  }
  std::cout<<std::endl;
}

template <typename T>
void Node<T>::remove(T _elem) {
  for(int i = 0; i < children.size(); i++){
    if(children[i]->get_elem() == _elem){
      delete children[i];
      children.erase(children.begin() + i);
      size--;
      return;
    }
  }
}
template <typename T>
T Node<T>::get_elem() {
  return elem;
}

#endif //ANTOSHA_TREE_H
