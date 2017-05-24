#include <iostream>

#define POISON -2

//=============================================================================

class ListElem		// класс описывает эдемент списка
{
public:
    int value;		// значение
    ListElem* next;	// следующий элемент
    ListElem* prev;	// предыдущий элемент

    ListElem();		// конструктор скласса
};

class List					// класс описывает двусвязный список замкнутый в кольцо
{
public:

    int NumberOfElem;		// количество элементов в списке
    ListElem* HeadOfList;	// указатель на голову списка

    List();					// конструктор класса
    ~List();				// деструктор класса
    void ListDump();			// функция печатает список на экран
    void AddToEnd(int value);	// функция добавляет элемент в конец списка
    void AddToBegin(int value);	// функция добавляет элемент в начало списка
    void DeleteFromEnd();		// функция удаляет элемент с конца списка
    void DeleteFromBegin();		// функция удаляет элемент с начала списка
    void Counter(int count);	// функция считалочка удаляет каждый count-ый элемент списка пока не останется один
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