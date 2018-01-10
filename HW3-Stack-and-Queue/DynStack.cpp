#include <iostream>
#include "DynStack.h"

using namespace std;

DynStack::DynStack()
{
	head = nullptr;
}

void DynStack::push(char value)
{
	StackNode *newnode;
	newnode = new StackNode;

	
	newnode->element = value; 

	if(IsEmpty())
	{
		newnode->next = nullptr;
		head = newnode;
	}
	else 
	{
	
		newnode->next = head;
		head = newnode;

	}



}

void DynStack::pop(char &value)
{

	if (!IsEmpty())
	{
		
		StackNode * temp = head;
		value = temp->element;

		head = head->next;
		
		delete temp;

	}


}

bool DynStack::IsEmpty()
{
	if(head == nullptr)
	{return true;}
	else
	{return false;}
}
