#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>


class Integral {
private:
    size_t numWorkers;      // количество потоков
    size_t numIterations;   // количество итераций для каждого потока
    std::vector<std::thread> workers;   // вектор с потоками
    std::vector<double> results;        // вектор с результатами для каждого потока

    void integrate(int worker_num, double f(double), double begin, double end) {
        double step = (end - begin) / numIterations;
        for (int i = 0; i < numIterations; ++i) {
            results[worker_num] += f(begin + step * i);
        }
        results[worker_num] = results[worker_num] * step;
    }

public:
    Integral(size_t numWorkers_, size_t numIterations_, double f(double), double begin, double end) :
            numWorkers(numWorkers_),
            numIterations(numIterations_),
            results(numWorkers_) {

        double step = (end - begin) / numWorkers;
        for (int i = 0; i < numWorkers; i++) {
            // в каждом потоке запускаем функцию `integrate`
            workers.emplace_back(
                    [this, i, f, step, begin]() {
                        integrate(i, f, begin + step * i, begin + step * (i + 1));
                    });
        }
    }

    double Calculate() {
        for (int i = 0; i < numWorkers; i++) {
            // ждём пока всё потоки закончат считать
            workers[i].join();
        }

        // суммируем всё, что насчитали
        double result = 0.0;
        std::for_each(results.begin(), results.end(), [&](double n) {
            result += n;
        });
        return result;
    }
};


double f(double x) {
    return x;
}

int main() {
    Integral integral(10, 100, f, 0, 10);
    std::cout << integral.Calculate() << std::endl;
    return 0;
}