#include <stdio.h>
#include "mylib.h"
#include "list.h"


int main() {
    
    HELLO("My list");
    
    List* list =  ListCtor();

    AddToEnd(list, 1);
    AddToEnd(list, 10);
    AddToEnd(list, 20);
    AddToEnd(list, 14);
    AddToEnd(list, 12);
    AddToEnd(list, 7);
    AddToEnd(list, 45);
    AddToEnd(list, -14);
    AddToEnd(list, 57);
    AddToEnd(list, 48);

    ListDump(list, "my list"); 

    AddToBegin(list, 0);
    AddToBegin(list, 0);

    ListDump(list, "my list");
    
    DeleteFromEnd(list);
    DeleteFromEnd(list);
    DeleteFromEnd(list);

    ListDump(list, "my list");

    DeleteFromBegin(list);
    DeleteFromBegin(list);
    DeleteFromBegin(list);

    ListDump(list, "my list");

    DeleteList(list);

    return 0;
}
