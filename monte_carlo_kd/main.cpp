//
// Created by antosha on 4/25/17.
//

#include <utility>
#include <iostream>
#include <thread>
#include <cmath>

using std::pair;
using std::cin;
using std::cout;


double funk(int k, double* args){
    return args[0]*args[1];
}

/*double funk(int k, double* args){
    double res = 0;
    for (int i = 0; i < k; ++i) {
        res += args[i];
    }
    return res;
}*/

class Integral{
public:
    double calculate();
    Integral(int k_, pair<double, double>* comp_, int n_, int accuracy);
    ~Integral();

private:
    int n;
    int k;
    int accuracy;
    pair<double, double>* comp;
    double * sums;
    std::thread* workers;
    void monte_carlo(int, int);
};

Integral::Integral(int k_, pair<double, double>* comp_, int n_, int accuracy_):
        n(n_), k(k_),
        comp(comp_),
        accuracy(accuracy_){
    sums = new double[n];
    workers = new std::thread[n];

    for (int i = 0; i < n; ++i) {
        workers[i] = std::thread([this, accuracy_, n_, i]() { monte_carlo(accuracy_ / n_, i);});
    }
}

Integral::~Integral(){
    delete sums;
    delete workers;
}

void Integral::monte_carlo(int numb, int i) {
    double* args = new double[k];
    for (int l = 0; l < numb; ++l) {
        for (int j = 0; j < k; ++j) {
            args[j] = ((double)rand() / RAND_MAX) * (comp[j].second - comp[j].first) + comp[j].first;
        }
        sums[i] += funk(k, args);
    }
    delete args;
}

double Integral::calculate() {
    double res = 0;
    for (int i = 0; i < n; ++i) {
        workers[i].join();
        res += sums[i];
    }
    res /=  (accuracy / n) * n;
    for (int j = 0; j < k; ++j) {
        res *= comp[j].second - comp[j].first;
    }

    return res;
}


int main(){
    srand(unsigned(time(0)));

    int n = 3;
    int k = 1;

    pair<double, double>* comp = new pair<double, double>[k];

    for (int i = 0; i < k; ++i) {
        cin >> comp[i].first >> comp[i].second;
    }

    Integral* mc = new Integral(k, comp, n, n*1000000);

    cout<< std::endl << std::endl << mc->calculate()<<std::endl;

    delete comp;

    return 0;
}
