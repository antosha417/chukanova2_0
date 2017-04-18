//
// Created by antosha on 01.03.17.
//

#include <vector>
#include <iostream>

int SHIFT = 0;

template <typename T>
class Node{
private:
    T elem;// тип данных в вершине
    std::vector<Node*> children
    ; //в векторе чилдрен храним указатели на детей
public:
    Node(T);
    ~Node();
    void insert(T);
    void remove(T);//удаляет всех детей и вершину
    Node<T>* find(T); // находит элемент по значению и возвращает указатель на элемент
    void dump();// печать
    T get_elem();// возвращает значение поля элемента
};

template <typename T>
Node<T>::Node(T _elem) {
    elem = _elem;
}

template <typename T>
Node<T>::~Node() {
    while(children.size() != 0){// пока есть дети удаляем детей
        delete children.back();// дает значение последнего элемента в векторе
        children.pop_back(); // удаляет последний элемент вектора
    }
}


template <typename T>
void Node<T>::insert(T _elem) {
    children.push_back(new Node<T>(_elem));//добавить объект класса ноуд
}

template <typename T>
Node<T>* Node<T>::find(T _elem) {
    Node<T>* res = NULL;
    if (elem == _elem) {
        return this; // вовзращаем указательна объект
    } else {
        for(int i = 0; i < children.size(); i++){ // функция вектора, которая возвращает размер вектора
            if (res == NULL) {
                res = children[i]->find(_elem); //
            } else {
                return res;
            }
        }
    }
    return res;
}

template <typename T>
void Node<T>::dump() { // печать
    for(int i = 0; i < SHIFT; i++){
        std::cout<< '\t';
    }
    std::cout<<elem;// вывели на экран элемент
    if (children.size() > 0) {
        int temp = SHIFT; // временная переменная temp
        SHIFT = 1;
        children[0]->dump();// вызвали печать от 0 ребенка
        if(children.size() > 1)
            SHIFT = temp + 1;// увеличиваем табьуляцию если есть дети
            for (int i = 1; i < children.size(); i++) {// печатаем остальных детей
                children[i]->dump();
            }
            SHIFT--;
    }
    std::cout<<std::endl;
}

template <typename T>
void Node<T>::remove(T _elem) {
    for(int i = 0; i < children.size(); i++){
        if(children[i]->get_elem() == _elem){ //если значение ребенка совпадает со значением, которое надо удалить, то удаляем его
            delete children[i]; // вызвали деструктор, удалили детей ребенка
            children.erase(children.begin() + i);//удаляется элемент и схлопывается массив
            return;
        }
    }
}
template <typename T>
T Node<T>::get_elem() {
    return elem;
}

int main(){
    Node<int>* tree = new Node<int>(10);//создали дерево,объявляем тип шаблона, выделили память под деревом
    tree->insert(9);
    tree->insert(8);
    tree->insert(7);

    tree->find(8)->insert(6);
    tree->find(8)->insert(5);
    tree->find(8)->insert(4);

    tree->find(7)->insert(3);
    tree->find(7)->insert(2);
    tree->find(7)->insert(1);

    tree->dump();

    tree->remove(8);

    tree->dump();


    delete tree;
    return 0;
}