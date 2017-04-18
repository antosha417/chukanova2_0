#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <algorithm>
#include "Tree.h"

template <typename T>
class FindElem {
 private:
  size_t numWorkers;
  std::vector<std::thread> workers;
  std::vector<std::mutex> mtxs;
  std::vector<std::queue<Node<T>*>> queues;
  std::atomic<size_t> done;
  Node<T>* head;
  Node<T>* key_elem;
  T elem;

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
    while (not done.load()) {
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
      if (currNode->getKey() == elem) {
        key_elem = currNode;
        done.fetch_add(1);
      }
      std::vector<Node<T>*> children = currNode->getChildren();
      for (int index = 0; index < children.size(); index++) {
        queues[number].push(children[index]);
      }
    }
  }
 public:

  FindElem(size_t numWorkers_, Node<T>* head_,T elem_ ):
      numWorkers(numWorkers_),
      mtxs(numWorkers_),
      queues(numWorkers_),
      done(0),
      head(head_),
      elem(elem_),
      key_elem(nullptr){

    for (int i = 0; i < numWorkers; i++) {
      workers.push_back(std::thread([this, i](){find(i);}));
    }
    queues[0].push(head);
  }

  Node<T>* Find() {
    for (int i = 0; i < numWorkers; i++) {
      workers[i].join();
    }
    return key_elem;
  }

  ~FindElem() {}
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


  FindElem<int> elem(3, tree, 5);
  elem.Find()->dump();
  return 0;
}