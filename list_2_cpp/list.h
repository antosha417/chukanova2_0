#include <iostream>

#define POISON -2

//=============================================================================

class ListElem
{
public:
    int value;
    ListElem* next;
    ListElem* prev;

    ListElem();
};

class List
{
public:

    int NumberOfElem;
    ListElem* HeadOfList;

    List();
    ~List();
    void ListDump();
    void AddToEnd(int value);
    void AddToBegin(int value);
    void DeleteFromEnd();
    void DeleteFromBegin();
    void Counter(int);
};

//=============================================================================

List::List()
{
	NumberOfElem = 0;
	HeadOfList = new ListElem();
	HeadOfList->next = HeadOfList;
	HeadOfList->prev = HeadOfList;
	HeadOfList->value = POISON;
}

//=============================================================================

List::~List()
{
    for (int i = 0; i < NumberOfElem; i++)
    {
        ListElem* temp = HeadOfList->prev;
        HeadOfList->prev = temp->prev;
        delete temp;
    }

	NumberOfElem = POISON;
	delete HeadOfList;
}

//=============================================================================

ListElem::ListElem()
{
	value = POISON;
	prev = NULL;
	next = NULL;

}

//=============================================================================

void List::ListDump()
{
	ListElem* temp = HeadOfList->next;
	printf("Number of elements = %d\n", NumberOfElem);
	for (int i = 0; i < NumberOfElem; i++)
	{
		printf("[%d] <%d>\n", i, temp->value);
		temp = temp->next;
	}
    std::cout<<std::endl;
}

//=============================================================================

void List::AddToEnd(int value)
{
	ListElem* temp = new ListElem();
	temp->value = value;
	
	temp->prev = HeadOfList->prev;

	HeadOfList->prev->next = temp;

	temp->next = HeadOfList;

	HeadOfList->prev = temp;

	NumberOfElem++;
}

//=============================================================================

void List::AddToBegin(int value)
{
	ListElem* temp = new ListElem();
	temp->value = value;
	
	temp->prev = HeadOfList;

	temp->next = HeadOfList->next;

    HeadOfList->next->prev = temp;

	HeadOfList->next = temp;

	NumberOfElem++;

}

//=============================================================================


void List::DeleteFromEnd()
{
	ListElem* temp = HeadOfList->prev;
	
	HeadOfList->prev = temp->prev;
	
	temp->prev->next = HeadOfList;

    delete temp;

	NumberOfElem--;
}

//=============================================================================

void List::DeleteFromBegin()
{

	ListElem* temp = HeadOfList->next;
	
	HeadOfList->next = temp->next;
	
	temp->next->prev = HeadOfList;

    delete temp;

	NumberOfElem--;
}

//=============================================================================

void List::Counter(int c) {
    ListElem* current = HeadOfList;
    while (NumberOfElem > 1) {
        for (int i = 0; i < c - 1; i++){
            current = current->prev;
            if (current == HeadOfList)
                i--;
        }

        ListElem* temp = current->prev;
        if (temp == HeadOfList){
            current = HeadOfList;
            temp = HeadOfList->prev;
        }

        current->prev = temp->prev;
        temp->prev->next = current;

        NumberOfElem --;
        delete temp;
        ListDump();
    }

}