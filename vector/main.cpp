//
// Created by antosha on 14.03.17.
//

#include <iostream>
#include <assert.h>

using std::cout;

template <typename T>
class MyVector{
private:
    unsigned len;
    unsigned max_len;
    T* elems;
public:
    unsigned get_len();
    MyVector();
    ~MyVector();
    void add(T);
    void remove(unsigned);
    void dump();
};


template <typename T>
unsigned MyVector<T>::get_len(){
    return len;
}

template <typename T>
void MyVector<T>::dump(){
    cout<<"<Class MyVector: len="<<len<<"| elems=[ ";
    for(int i = 0; i < len - 1; i++){
        cout<<elems[i]<<", ";
    }
    cout<<elems[len - 1];
    cout<<" ]"<<std::endl;
}

template <typename T>
MyVector<T>::MyVector(){
    max_len = 4;
    elems = new T[max_len];
    len = 0;
}

template <typename T>
MyVector<T>::~MyVector(){
    max_len = 0;
    delete elems;
    len = 0;
}

template <typename T>
void MyVector<T>::add(T elem){
    if(max_len - len == 1){
        max_len *= 2;
        T* new_elems = new T[max_len];
        for(int i = 0; i < len; i++){
            new_elems[i] = elems[i];
        }
        delete elems;
        elems = new_elems;
    }
    elems[len] = elem;
    ++len;
}

template <typename T>
void MyVector<T>::remove(unsigned num){
    assert(num < len);
    for(int i = num; i < len-1; i++){
        elems[i] = elems[i+1];
    }
    --len;
}


int main(){

    MyVector<int>* a = new MyVector<int>();
    for (int i = 0; i < 20; ++i){
        a->add(i);
    }

    a->dump();

    a->remove(7);
    a->remove(6);
    a->remove(5);
    a->remove(0);

    a->dump();

    return 0;
}