
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;


struct node
{
	string data;  // studentID in string
	node *next;

	node::node()
	{}

	node::node(const string &s, node * link)
		: data(s), next(link)
	{}
};

class linkedlist
{

	friend class linkedlistiterator;

private:
	node *head;		//Head node, start of LinkedList

public:
	linkedlist();			    //Constructor
	linkedlist(const linkedlist & copy);	//Copy constructer
	~linkedlist ();   //destructor
	void printList();		    //Prints the given LinkedList from head to end
	void addSorted(string n);   //Insert a new node such that the list is sorted
	
	void pop(string &value);   //Insert a new node such that the list is sorted
	const linkedlist linkedlist:: operator + (const linkedlist & rhs);
	const linkedlist linkedlist:: operator - (const linkedlist & rhs);
	string linkedlist:: operator [] (int index);
	void linkedlist::deletenode(string &data);
	bool IsEmpty();
	node * createClone() const;
	node * getHead() const;


};

class linkedlistiterator
{
	public:
	linkedlistiterator(const linkedlist & list) : mylist(list), mycurrent(nullptr)
	{ }
     
	void Init()
	{	currentindex = 0;
		mycurrent = mylist.head;  // first node
	}

	bool HasMore() const
	{   return (mycurrent != nullptr);
	}

	string Current() const
	{  
		return mycurrent->data;
	}

	void Next()
	{   
		mycurrent = mycurrent->next;
		currentindex++;
	}

	int getCurrentIndex()
	{   
		return currentindex;
	}

	private:
	const linkedlist & mylist;
    node * mycurrent;
	int currentindex;
};


#endif