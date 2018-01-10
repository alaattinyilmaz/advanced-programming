#include <iostream>
#include "DynQ.h"

using namespace std;

DynQ::DynQ()
{

	head = nullptr;
	tail = nullptr;

}


void DynQ::qadd(char value)
{

	QueueNode *newnode = new QueueNode(value);

	if(IsEmpty())
	{
		head = newnode;
		tail = newnode;
	}

	else 
	{
		tail->next = newnode;
		tail = newnode;
	}


}

void DynQ::qdrop(char &value)
{

	if(!IsEmpty())
	{
		value = head->element;
		QueueNode *temp = head;
		head = head->next;
		delete temp;
	}

}

bool DynQ::IsEmpty() const
{
	if(head == nullptr)
	{return true;}
	else 
	{return false;}
}