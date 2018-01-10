#include <iostream>
#include <string>
#include "linkedlist.h"

using namespace std;

linkedlist::linkedlist()
{

	head = nullptr;

}

linkedlist::linkedlist(const linkedlist & copy) // Copy constructer
{

	head = copy.createClone();

}

void linkedlist::printList()
// Prints all the data in the list
{

	if(IsEmpty())
	{
		cout << "List is empty" << endl;
	}

	else {

		node * ptr = head;

		while(ptr)
		{
			cout << ptr->data << endl;
			ptr = ptr->next;

		}
	}
}

void linkedlist::addSorted(string n)
// Adds certain n string to the list in order
{
	if(head == nullptr || n < head->data && n != head->data)
	{
		node * newnode = new node;
		newnode->data = n;
		newnode->next = head;
		head = newnode;
	}

	else if(n > head->data)
	{
		node * ptr = head;

		while(ptr->next && n >= ptr->next->data) // ptr goes to last node which is less than n
		{
			ptr = ptr->next;
		}

		if(ptr->data != n) // If it occured once in the list it does not add to the list
		{

			node * newnode = new node;
			newnode->data = n;
			newnode->next = ptr->next;
			ptr->next = newnode;

		}

	}


}	

node * linkedlist::createClone () const 
// Helper function to create a deep copy 
{

	if(head == nullptr)
	{return nullptr;}

	node * headclone = new node;
	// Creating of first node with the same data of original one
	headclone->data = head->data;
	headclone->next = nullptr;

	node * ptr = head->next;
	node * ptrclone = headclone;

	while(ptr) // Creating of other copies of other nodes
	{
		ptrclone->next = new node;
		ptrclone->next->data = ptr->data;
		ptrclone->next->next = nullptr;
		ptr = ptr->next;
		ptrclone = ptrclone->next;
	}

	return headclone;
}

const linkedlist linkedlist::operator+(const linkedlist & course2)
// Union operator which takes right hand side (course2 in this case) as paramater
{

	linkedlist clonelist(course2); // Cloning of right hand side list

	node * ptr = head;

	while(ptr)
	{
		clonelist.addSorted(ptr->data); // Adding nodes of left hand side list
		ptr = ptr->next;
	}

	return clonelist;
}

const linkedlist linkedlist::operator-(const linkedlist & rhs)
// Difference operator which takes right hand side as paramater
{

	linkedlist clonelist(*this); // Cloning of first linkedlist

	node * ptr = head;
	node * rptr;

	while(ptr) 
	{
		rptr = rhs.head;

		while(rptr)
		{
			if(rptr->data == ptr->data) // Checking nodes which has same data with second list
			{
				clonelist.deletenode(ptr->data); // Deleting this same node from the first list
			}
			rptr = rptr->next;
		}

		ptr = ptr->next;
	}

	return clonelist;

}


string linkedlist::operator[](int index)

{

	if(IsEmpty())
	{
		return "The list is empty\n";
	}

	{
		linkedlistiterator itr(*this); // Creating of a iterator on list

		int numberofnodes = 0;

		// Counting all the nodes with iterator
		for (itr.Init(); itr.HasMore(); itr.Next())
		{numberofnodes++;}


		if(numberofnodes <= index) // If number of nodes is less than wanted index it gives an error message
		{
			return "out of bound\n";
		}

		else {


			itr.Init(); // Initialization to first node of the linkedlist 
			while(itr.getCurrentIndex() < index) // Checking every node
			{itr.Next();}

			return itr.Current();

		}
	}
}

void linkedlist::deletenode(string & data)
// Deletes a certain node from the linked list
{
	node * ptr = head;

	while(ptr)

	{
		if(head->data == data)
		{
			node * temp = head;
			head = head->next;
			delete temp;
			break;
		}

		else if(ptr->next && ptr->next->data == data) // When it finds the data, deletes it
		{
			node * temp = ptr->next;
			ptr->next = ptr->next->next;
			delete temp;
			temp = nullptr;
			break;
		}

		ptr = ptr->next;
	}
}

bool linkedlist::IsEmpty()
// Checks the linkedlist is empty or not
{
	if(head==nullptr)
		return true;
	else 
		return false;
}

node * linkedlist::getHead() const
{
	return head;
}

linkedlist::~linkedlist ()
// Destructor function visits all nodes and returns to heap
{
	node * ptr = head;
	while (ptr) 
	{
		node * temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

