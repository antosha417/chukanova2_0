#include "RBTree.h"
#include <iostream>

int main() {
    CRBTree<int>* tree = new CRBTree<int>();
    std::cout << tree->Insert(3);
    tree->Insert(4);
    tree->Insert(2);
    tree->Insert(5);
    tree->Insert(1);
    tree->Dump();
    tree->Delete(1);
//    tree->Dump();
    std::cout << tree->Has(3) << std::endl;
    tree->Dump();
    return 0;
}