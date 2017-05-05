//
// Created by Nikitos
//


#include <iostream>
#include <thread>
#include <vector>


int cmp(int a, int b){
    return a > b;
}


class merge_sort{
public:
    std::vector<std::thread> t;
    std::vector<int*> res;
    std::vector<int> lens;
    int num_workers;

    void sort(int*, int, int);

    void merge(int*, int*, int, int, int);

    merge_sort(int*, int, int);

    int* Sort();
};

int* merge_sort::Sort(){
    for (int i = 0; i < num_workers; ++i) {
        t[i].join();
    }
    for (int j = 1; j < num_workers; ++j) {
        merge(res[0], res[j], lens[0], lens[j], 0);
    }
    return res[0];
}


merge_sort::merge_sort(int* m, int n, int num_workers_){
    num_workers = num_workers_;
    for (int j = 0; j < num_workers; ++j) {
        res.push_back(nullptr);
        lens.push_back(0);
    }
    for (int i = 0; i < num_workers - 1; ++i) {
        t.push_back(std::thread([this, m, i, n]{this->sort(m + i*(n/num_workers), n/num_workers, i);}));
    }
    t.push_back(std::thread([this, m, n](){this->sort(m + (num_workers-1)*(n/num_workers), n - (num_workers-1)*n/num_workers, num_workers - 1);}));
}

void merge_sort::merge(int* p1, int* p2, int m1, int m2, int i){
    int n = m1 + m2;

    int n1 = 0;
    int n2 = 0;

    int* temp = new int[n];

    for (int i = 0; i < n; ++i) {
        if(n1 == m1){
            temp[i] = p2[n2];
            n2 ++;
        } else if(n2 == m2){
            temp[i] = p1[n1];
            n1 ++;
        } else if (cmp(p1[n1], p2[n2])){
            temp[i] = p1[n1];
            n1 ++;
        } else {
            temp[i] = p2[n2];
            n2 ++;
        }
    }
    res[i] = temp;
    lens[i] = n;
}

void merge_sort::sort(int* m, int n, int i){
    if (n == 1){
        res[i] = m;
        return;
    }

    int* p1 = m;
    int* p2 = m + n/2;

    sort(p1, n/2, i);
    p1 = res [i];
    sort(p2, n - n/2, i);
    p2 = res[i];

    merge(p1, p2, n/2, n - n/2, i);
}


int main(){

    int n = 28;

    int* m = new int[n];

    for (int i = 0; i < n; ++i) {
        m[i] = rand();
    }

    for (int j = 0; j < n; ++j) {
        std::cout<<m[j]<< ' ';
    }

    merge_sort* a = new merge_sort(m, n, 2);

    int* b = a->Sort();

    std::cout<<std::endl;

    for (int k = 0; k < n; ++k) {
        std::cout<<b[k]<< ' ';
    }

    return 0;
}
