

#define POISON -2

//=============================================================================

struct ListElem
{
	int value;
	ListElem* next;
	ListElem* prev;
};

struct List
{
	int NumberOfElem;
	ListElem* HeadOfList;
};


//=============================================================================

List* ListCtor();

void ListDtor(List * This);

ListElem* ListElemCtor();

void ListElemDtor(ListElem * This);

void DeleteList(List * This);

bool ListOk(List * This);

void ListDump(List * This, const char* name);

void AddToEnd(List* This, int value);

void AddToBegin(List* This, int value);

void DeleteFromEnd(List* This);

void DeleteFromBegin(List* This);

//=============================================================================

List* ListCtor()
{
	List* This = (List*)calloc(1, sizeof(*This));

	assert(This);
	This->NumberOfElem = 0;
	This->HeadOfList = ListElemCtor();
	This->HeadOfList->next = This->HeadOfList;
	This->HeadOfList->prev = This->HeadOfList;
	This->HeadOfList->value = POISON; 
	return This;
}

//=============================================================================

void ListDtor(List * This)
{
	ASSERT_OK(List, This);
	This->NumberOfElem = POISON;
	ListElemDtor(This->HeadOfList);
	free(This);
	This = NULL;
}

//=============================================================================

ListElem* ListElemCtor()
{
	ListElem* This = (ListElem*)calloc(1,sizeof(*This));

	assert(This);
	This->value = POISON;
	This->prev = NULL;
	This->next = NULL;

	return This;
}

//=============================================================================

void ListElemDtor(ListElem * This)
{
	assert(This);
	This->value = POISON;
	This->prev = NULL;
	This->next = NULL;
	free(This);
	This = NULL;
}

//=============================================================================

void DeleteList(List * This)
{	
	ASSERT_OK(List, This);

	for (int i = 0; i < This->NumberOfElem; i++)
	{
		ListElem* temp = This->HeadOfList->prev;
		This->HeadOfList->prev = temp->prev;
	}

	ListDtor(This);
}

//=============================================================================

bool ListOk(List * This)
{
	return This && This->NumberOfElem >=0 && 
		   This->HeadOfList->prev && This->HeadOfList->next;
}

//=============================================================================

void ListDump(List * This, const char* name)
{
	printf("\n%s", name);
	if(ListOk(This))
		printf(" (ok)\n");
	else
		printf(" (ERROR!)\n");
	ListElem* temp = This->HeadOfList->next;
	printf("Number of elements = %d\n", This->NumberOfElem);
	for (int i = 0; i < This->NumberOfElem; i++)
	{
		printf("[%d] <%d>\n", i, temp->value);
		temp = temp->next;
	}
}

//=============================================================================

void AddToEnd(List * This, int value)
{
	ASSERT_OK(List, This);

	ListElem* temp = ListElemCtor();
	temp->value = value;
	
	temp->prev = This->HeadOfList->prev;

	This->HeadOfList->prev->next = temp;

	temp->next = This->HeadOfList;

	This->HeadOfList->prev = temp;

	This->NumberOfElem++;

	ASSERT_OK(List, This);
}

//=============================================================================

void AddToBegin(List * This, int value)
{
	ASSERT_OK(List, This);

	ListElem* temp = ListElemCtor();
	temp->value = value;
	
	temp->prev = This->HeadOfList;

	temp->next = This->HeadOfList->next;

    This->HeadOfList->next->prev = temp;

	This->HeadOfList->next = temp;

	This->NumberOfElem++;

	ASSERT_OK(List, This);
}

//=============================================================================


void DeleteFromEnd(List* This)
{
	ASSERT_OK(List, This);

	ListElem* temp = This->HeadOfList->prev;
	
	This->HeadOfList->prev = temp->prev;
	
	temp->prev->next = This->HeadOfList;

    ListElemDtor(temp);

	This->NumberOfElem--;

	ASSERT_OK(List, This);
}

//=============================================================================

void DeleteFromBegin(List* This)
{
	ASSERT_OK(List, This);

	ListElem* temp = This->HeadOfList->next;
	
	This->HeadOfList->next = temp->next;
	
	temp->next->prev = This->HeadOfList;

    ListElemDtor(temp);

	This->NumberOfElem--;

	ASSERT_OK(List, This);
}

//=============================================================================
