#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <algorithm>
#include "Tree.h"

template <typename T>
class FindSum {
 private:
  size_t numWorkers;
  std::vector<std::thread> workers;
  std::vector<std::mutex> mtxs;
  std::vector<std::queue<Node<T>*>> queues;
  std::vector<T> sums;
  std::atomic<size_t> done;
  Node<T>* head;

  Node<T>* walk(int number) {
    for (int i = 0; i < numWorkers; i++) {
      if (i == number) {
        continue;
      }
      if (mtxs[i].try_lock()) {
          if (!queues[i].empty()) {
              Node<T> *node = queues[i].front();
              queues[i].pop();
              mtxs[i].unlock();
              return node;
          }
          mtxs[i].unlock();
      }
    }
    return nullptr;
  }

  void find(int i) {
    int number = i;
    while (done.load() < head->getSize()) {
        std::unique_lock<std::mutex> m(mtxs[i]);
      Node<T>* currNode = nullptr;
      if (!queues[i].empty()) {
        currNode = queues[i].front();
        queues[i].pop();
          m.unlock();
      } else {
        m.unlock();
        currNode = walk(number);
      }
      if (currNode == nullptr) {
        continue;
      }
      sums[number] += currNode->getKey();

      std::vector<Node<T>*> children = currNode->getChildren();
      for (int index = 0; index < children.size(); index++) {
          queues[number].push(children[index]);
      }
      done.fetch_add(1);
    }
  }
 public:
  FindSum(size_t numWorkers_, Node<T>* head_):
      numWorkers(numWorkers_),
      mtxs(numWorkers_),
      queues(numWorkers_),
      sums(numWorkers_),
      done(0),
      head(head_){

    for (int i = 0; i < numWorkers; i++) {
      workers.push_back(std::thread([this, i](){find(i);}));
    }
    queues[0].push(head);
  }

  T Find() {
    T sum = 0;
    for (int i = 0; i < numWorkers; i++) {
      workers[i].join();
      sum += sums[i];
    }

    return sum;
  }

  ~FindSum() {}
};

int main() {
  Node<int>* tree = new Node<int>(10);
  tree->insert(9);
  tree->insert(8);
  tree->insert(7);

  tree->dump();

  //tree->remove(8);
  //tree->dump();

  FindSum<int> sum(2, tree);
  std::cout << sum.Find() << std::endl;
  return 0;
}