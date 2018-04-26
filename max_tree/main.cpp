#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <algorithm>
#include "../max_tree/Tree.h"

template <typename T>
class FindMax {
 private:
  size_t numWorkers;
  std::vector<std::thread> workers;
  std::vector<std::mutex> mtxs;
  std::vector<std::queue<Node<T>*>> queues;
  std::vector<T> maxes;
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
      } else {
        m.unlock();
        currNode = walk(number);
      }
      if (currNode == nullptr) {
        continue;
      }
      if (currNode->getKey() > maxes[number]) {
        maxes[number] = currNode->getKey();
      }
      std::vector<Node<T>*> children = currNode->getChildren();
      for (int index = 0; index < children.size(); index++) {
        queues[number].push(children[index]);
      }
      done.fetch_add(1);
    }
  }
 public:
  FindMax(size_t numWorkers_, Node<T>* head_):
      numWorkers(numWorkers_),
      mtxs(numWorkers_),
      queues(numWorkers_),
      maxes(numWorkers_),
      done(0),
      head(head_){

    for (int i = 0; i < numWorkers; i++) {
      workers.push_back(std::thread([this, i](){find(i);}));
    }
    queues[0].push(head);
  }

  T Find() {
    for (int i = 0; i < numWorkers; i++) {
      workers[i].join();
    }
    return *std::max_element(maxes.begin(), maxes.end());
  }

  ~FindMax() = default;
};

int main() {
  Node<int>* tree = new Node<int>(10);
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


  tree->dump();

  //tree->remove(8);
  //tree->dump();

  FindMax<int> max(3, tree);
  std::cout << max.Find() << std::endl;
  return 0;
}