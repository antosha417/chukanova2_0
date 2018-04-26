#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <algorithm>
#include "Tree.h"

template<typename T>
class FindElem {
private:
    size_t numWorkers;
    std::vector<std::thread> workers;
    std::vector<std::mutex> mtxs;             // вектор мьютексов для блокировки очередей
    std::vector<std::queue<Node<T> *>> queues; // вектор очередей
    std::atomic<size_t> done;                 // нашли ли нужный элемент
    std::atomic<size_t> watched;              // количество просмотренных вершин
    Node<T> *head;                            // корень дерева
    Node<T> *key_elem;                        // найденый элемент в дереве
    T elem;

    /*
     * Функция принимает номер потока.
     * Проходит по очередям других потоков и пытается украсть оттуда какую-нибудь вершину.
     * Если не получилось возвращает `nullptr`.
    */
    Node<T> *walk(int number) {
        for (int i = 0; i < numWorkers; i++) {
            if (i == number) {
                continue;
            }
            if (mtxs[i].try_lock()) {         // блокируем чужую очередь
                if (!queues[i].empty()) {
                    Node<T> *node = queues[i].front();
                    queues[i].pop();          // если не пуста, возвращаем первый элемент
                    mtxs[i].unlock();
                    return node;
                }
                mtxs[i].unlock();
            }
        }
        return nullptr;
    }

    /*
     * Функция принимает номер потока.
     * Берёт из своей очереди вершину сравнивает её значение
     *
    */
    void find(int number) {
        while (watched.load() < head->getSize()) {

            if (done.load() > 0) break;

            std::unique_lock<std::mutex> m(mtxs[number]);   // блокируем свою очередь
            Node<T> *currNode = nullptr;
            if (!queues[number].empty()) {                  // если она не пуста убираем из очереди первый элемент
                currNode = queues[number].front();          // и кладём его в `currNode`
                queues[number].pop();
            } else {                                        // если пуста, то
                m.unlock();                                 // разблокируем свою очередь
                currNode = walk(number);                    // и идём гулять по чужим
            }
            if (currNode == nullptr) {
                continue;
            }
            if (currNode->getKey() == elem) {
                key_elem = currNode;
                done.fetch_add(1);
            }
            std::vector<Node<T> *> children = currNode->getChildren();
            for (int index = 0; index < children.size(); index++) {
                queues[number].push(children[index]);        // добавляем всех детей текущей вершины в свою очередь
            }
            watched.fetch_add(1);
        }
    }

public:

    FindElem(size_t numWorkers_, Node<T> *head_, T elem_) :
            numWorkers(numWorkers_),
            mtxs(numWorkers_),
            queues(numWorkers_),
            done(0),
            watched(0),
            head(head_),
            elem(elem_),
            key_elem(nullptr) {

        // в каждом потоке запустим функцию `find` с номером этого потока
        for (int i = 0; i < numWorkers; i++) {
            workers.push_back(std::thread([this, i]() { find(i); }));
        }

        // добавим корень дерева в очередь нулевого потока
        queues[0].push(head);
    }

    Node<T> *Find() {
        for (int i = 0; i < numWorkers; i++) {
            workers[i].join();
        }
        return key_elem;
    }

};

int main() {
    // создадим и заполним дерево
    Node<int> *tree = new Node<int>(10);
    tree->insert(9);
    tree->insert(8);
    tree->insert(7);

    tree->find(8)->insert(6);
    tree->find(8)->insert(5);
    tree->find(8)->insert(4);

    tree->find(7)->insert(3);
    tree->find(7)->insert(2);
    tree->find(7)->insert(1);

    tree->find(5)->insert(33);
    tree->find(5)->insert(21);
    tree->find(5)->insert(10);

    // нарисуем дерево
    tree->dump();

    // запустим поиск 5-ки в дереве на 3-ёх потоках
    FindElem<int> elem(3, tree, 5);

    // нарисуем поддерево которое нашли
    Node<int> *found = elem.Find();

    if (found != nullptr) {
        std::cout<<"Найденное поддерево:"<<std::endl;
        found->dump();
    } else {
        std::cout << "Не удалось найти элемент" << std::endl;
    }
    return 0;
}