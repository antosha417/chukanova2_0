#include <stdio.h>
#include "list.h"


int main() {

    List* list =  new List();

    list->AddToEnd(1);
    list->AddToEnd(2);
    list->AddToEnd(3);
    list->AddToEnd(4);
    list->AddToEnd(5);
    list->AddToEnd(6);
    list->AddToEnd(7);
    list->AddToEnd(8);
    list->AddToEnd(9);
    list->AddToEnd(10);
    list->AddToEnd(11);


    list->ListDump();

    list->Counter(3);

    return 0;
}
