#include <stdio.h>
#include "list.h"


int main() {

    List* list =  new List();

    for (int i = 0; i < 7; ++i) {
        list->AddToEnd(i);
    }

    list->ListDump();

    for (int i = 7; i < 9; ++i) {
        list->AddToBegin(i);
    }

    list->ListDump();

    list->DeleteFromBegin();
    list->DeleteFromEnd();

    list->ListDump();

    list->Counter(3);

    delete list;

    return 0;
}
