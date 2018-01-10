#include <iostream>
#include "linkedlist.h"
#include <string>

using namespace std;


const linkedlist operator&(const linkedlist & lhs, const linkedlist & rhs)
// Free function which gives intersection of two list
{

	linkedlist intersection;

	node * ptr = lhs.getHead();
	node * rptr;

	while(ptr)
	{
		rptr = rhs.getHead();

		while(rptr)
		{
			if(rptr->data == ptr->data) // Puts same datas into another linkedlist
			{
				intersection.addSorted(rptr->data);
			}
			rptr = rptr->next;
		}

		ptr = ptr->next;
	}

	return intersection;
}

void DisplayMenu(linkedlist & course1, linkedlist & course2)
{
	cout << 
		"***************************" << endl <<
		"* 1. union(+) *" << endl <<
		"* 2. difference(-) *"<< endl << 
		"* 3. Intersection (&) *"<< endl <<
		"* 4. [] operator *" << endl <<
		"* 5. Exit *"<< endl <<
		"***************************" << endl;

	string choice;

	cin >> choice;

	if(choice == "1")
	{
		cout << "Your choice is: 1 " << endl << "Union of two lists are:" << endl;

		// Union of two list
		linkedlist unionlist = course1 + course2;
		unionlist.printList();

		DisplayMenu(course1, course2);

	}
	else if(choice == "2")
	{

		cout << "Your choice is: 2 " << endl;

		cout << "Enter the lhs list: ";
		string lhs;
		cin >> lhs;

		if(lhs == "1")
		{
			
			cout << "difference of list1-list2 is:" << endl;
			linkedlist unionlist = course1 - course2; // Difference of two lists
			unionlist.printList();

		}

		else if(lhs == "2")

		{

			cout << "difference of list2-list1 is:" << endl;
			linkedlist unionlist = course2 - course1;
			unionlist.printList();

		}

		DisplayMenu(course1, course2);

	}
	else if(choice == "3")
	{

		cout << "Your choice is: 3 " << endl;
		cout << "intersection of list1 and list2 is:" << endl;

		linkedlist intersection = course2 & course1; // Intersection of two lists
		intersection.printList(); 
		
		DisplayMenu(course1, course2);

	}

	else if(choice == "4")
	{

		cout << "Your choice is: 4 " << endl;


		cout << "Enter the list number: ";
		int listnumber;
		cin >> listnumber;

		if(listnumber==1)
		{

			cout << "Enter an index number: ";
			int index;
			cin >> index;
			cout << "The index " << index << " of the list is:" <<endl;
			cout << course1[index] << endl; // Giving wanted index of a linkedlist
		}

		else if (listnumber==2)
		{

			cout << "Enter an index number: ";
			int index;
			cin >> index;
			cout << "The index " << "" << " of the list is:" <<endl;
			cout << course2[index] << endl;

		}

		DisplayMenu(course1,course2);


	}
	else if(choice == "5")
	{
		cout << "Program exitting..." << endl;
		// Destructer of linkedlist class will help all memory to turn into heap
		return;
	}


}
int main()
{
	string coursename, coursename2;
	cout << "Enter the name of the course: ";
	cin >> coursename;
	cout << "Course " << coursename << " registration list" << endl;

	string studentid;

	linkedlist course1, course2;


	while(cin)
	{
		cout << "Please enter a studentID!" << endl;
		cin >> studentid;
		if(cin) // Checking if user enters CTRL+Z or not
		course1.addSorted(studentid);
	}


	cout << endl << "List of students who registered for course "<< coursename << " is: " << endl;
	course1.printList(); // Printing of all students in course 1

	cin.ignore();
	cin.clear();

	cout << endl;

	cout << "Enter the name of the course: ";
	cin >> coursename2;
	cout << "Course " << coursename2 << " registration list" << endl;

	while(cin)
	{
		cout << "Please enter a studentID!" << endl;
		cin >> studentid;
		if(cin)
		course2.addSorted(studentid);
	}

	cin.ignore();
	cin.clear();

	cout << endl << "List of students who registered for course "<< coursename2 << " is: " << endl;
	course2.printList(); // Printing of all students in course 2
	cout << endl;
	DisplayMenu(course1, course2);


}