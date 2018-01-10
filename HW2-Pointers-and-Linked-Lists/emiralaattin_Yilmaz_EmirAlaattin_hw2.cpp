#include <iostream>
#include <string>
#include "date.h"

using namespace std;


struct BorrowInfo
{
	int studentID;
	Date borrowDate;
	Date returnDate;
	BorrowInfo *next;
	BorrowInfo *prev;
};

struct Book
{
	int bookID;
	string bookName;
	Book *next;
	BorrowInfo *borrowInfos;
};


void DisplayMenu(Book * head);
void Displayer(Book * head);
void DisplayBooks(Book * head);
void AddaBook(Book * head);
void BorrowOrRefund(Book * head);
bool Exist(int id, Book *head);
void InfoTaker(int bookid, Book * head);
void DisplayBorrowed(Book * head,string choice);


bool BRExist(int bookid, int studentid, Book *head)
	// This function checks if there is a student with studentid who borrows a book with bookid 
{
	Book * ptr = head;

	while(ptr != nullptr)
	{
		if (ptr->bookID == bookid) // Searching among books
		{
			BorrowInfo *ptrborrow = ptr->borrowInfos;

			while(ptrborrow->next != nullptr) // Searching among infos of books
			{
				if(ptrborrow->studentID == studentid) // If it finds it returns true
				{
					return true;
				}

				else
				{
					ptrborrow = ptrborrow->next;
				}

			}

		}

		ptr = ptr->next; 

	}

	return false;

}

void DisplayBorrowed(Book * head, string choice)
	// This function shows borrowed books according to user's choice
{

	if (choice == "previously")
	{
		cout << "Enter ID of the students to see all books previously borrowed by him/her:";
	}
	else if (choice == "currently")
	{
		cout << "Enter ID of the students to see all books previously borrowed by him/her:";
	}
	int studentid;
	cin >> studentid;


	Book * ptr = head;

	Date today = Date();


	while (ptr != nullptr) // searching the books
	{

		BorrowInfo *borrow = ptr->borrowInfos;

		while (borrow->next != nullptr) // searching the book infos of the book which one pointed by ptr pointer
		{

			if (borrow->studentID == studentid)
			{
				if(choice == "previously")
				{

					if (borrow->borrowDate < today) // checking the previous ones

					{
						cout << "Book ID: " << ptr->bookID << " Name: " << ptr->bookName <<  endl;
					}

				}

				else if (choice == "currently")
				{
					if (borrow->returnDate > today) // checking the current ones

					{
						cout << "Book ID: " << ptr->bookID << " Name: " << ptr->bookName <<  endl;
					}

				}
			}

			borrow = borrow->next; // next book info

		}

		ptr = ptr->next;

	}
	DisplayMenu(head);

}

void DisplayBookInfo(Book * head)
	// This function calls another function which displays circulation of the books in reverse chronological order
{

	cout << "Enter ID of the book for displaying its circulation in reverse chronological order:";
	int bookid;
	cin >> bookid;


	if(!Exist(bookid, head)) // checking the book exists or not
	{
		cout << "The book is not exists!" << endl << endl;
		DisplayMenu(head);
	}

	else 
	{

		InfoTaker(bookid, head); // Calling InfoTaker func to display circulation
		DisplayMenu(head);

	}

}

void InfoTaker(int bookid, Book *head)
{
	//This function displays circulation of the books in reverse chronological order


	Book * ptr = head;

	BorrowInfo * headborrow; // will be always new ptr book's first info in the while below


	while(ptr != nullptr)
	{

		if(ptr->bookID == bookid)
		{
			headborrow = ptr->borrowInfos; // First borrowinfo of the book which pointed by ptr
			BorrowInfo * pbor = headborrow;



			if (pbor->next == nullptr)
			{
				cout << "Circulation info for this book not exists." << endl << endl;
			}

			else {

				cout << "StudentID \t"  << "BorrowDate \t" << "ReturnDate \t" << endl;

				while(pbor->next->next != nullptr) // pbor pointer is going to the end of linkedlist
				{
					pbor = pbor->next;

				}
				while(pbor->prev != nullptr) // and then it is coming back from the end to show nodes in reverse order
				{
					cout << pbor->studentID << "\t\t" << pbor->borrowDate << "\t\t" << pbor->returnDate << " \t\t"<< endl;

					pbor = pbor->prev;

				} 
				cout << pbor->studentID << "\t\t" << pbor->borrowDate << "\t\t" << pbor->returnDate << " \t\t"<< endl;

			}

		}

		ptr = ptr->next;

	} 

}

bool Exist(int id, Book *head)
	// This function checks if a book exist or not with bookid = id
{

	Book * ptr = head;

	while(ptr != nullptr)
	{
		if (ptr->bookID == id) // if it finds it returns true
		{return true;}
		else 
		{ ptr = ptr->next; }
	}

	return false;

}

void BorrowOrRefund(Book * head)
	// This function doing the borrowing actions and borrow checks
{
	int bookid;

	cout << "Enter the ID of the book: ";
	cin >> bookid;

	if(!Exist(bookid, head)) // checking the book is exist or not
	{
		cout << "The book is not exist to be borrowed." << endl;
		DisplayMenu(head);
	}

	else 
	{
		char choice;

		cout << "Do you want Borrow or return the book(press B for borrow and R for return): ";
		cin >> choice;

		if(choice == 'B' || choice == 'b')
		{

			cout << "Enter the ID of the Student: ";

			int studentid;
			cin >> studentid;

			cout << "Enter the start date for borrowing the book in format DD MM YYYY: ";

			int dd, mm, yyyy;
			cin >> dd;
			cin >> mm;
			cin >> yyyy;

			if (BRExist(bookid, studentid, head)) // Checking student if it borrows the book more than once
			{

				cout << "Student with ID:" << studentid << " could not borrow the book more than once." << endl << endl;

				DisplayMenu(head);

			}

			else { 

				Date borrowdate (mm, dd, yyyy); 
				Date returndate = borrowdate + 30; 

				Book * ptr = head;

				while(ptr != nullptr)
				{

					if(ptr->bookID == bookid) // finding THE book
					{

						BorrowInfo *headborrow = ptr->borrowInfos;

						BorrowInfo *newborrow = new BorrowInfo; // creating new borrowinfo node

						newborrow->studentID = studentid;
						newborrow->borrowDate = borrowdate;
						newborrow->returnDate = returndate;
						// assigning its values above


						if(borrowdate < headborrow->borrowDate)
						// if its borrowdate smaller than head's borrowdate this node will be at the head now
						{


							if (returndate > headborrow->borrowDate)
							{

								cout << "You could not borrow this book. The book is on hold untill: " << headborrow->returnDate;

							}

							else {

							// new borroy holds the head borrow from left

								newborrow->next = headborrow;
								newborrow->prev = nullptr;

								headborrow->prev = newborrow;

								headborrow = newborrow;

								ptr->borrowInfos = headborrow;

								cout << "Borrow information for book ID " << bookid << " and student ID " << studentid << " is added to the list." << endl << endl;

							}
						}

						else {
							
							// if borrowdate of new node is higher than the head node it will be at the right of the head

							BorrowInfo * ptrborrow = headborrow;


							while (ptrborrow->next != nullptr && ptrborrow->next->borrowDate < borrowdate) 
							// node is trying to find its real place checking every node if it is higher or less than this node
							{   
								ptrborrow = ptrborrow->next;
							} 

							if(borrowdate < ptrborrow->returnDate)
							{

								cout << "You could not borrow this book. The book is on hold since: " << ptrborrow->returnDate << endl << endl;

							}
							else if (returndate > ptrborrow->next->borrowDate)
							{

								cout << "You could not borrow this book. The book is on hold untill: " << ptrborrow->next->returnDate << endl << endl;

							}

							else {

						// when new node finds its place it holds to two nodes it is now between of them it can not be in the end because the end one is so big date (01 01 2500)

								BorrowInfo *temp = ptrborrow->next;

								ptrborrow->next = newborrow;
								newborrow->prev = ptrborrow;

								newborrow->next = temp;
								temp->prev = newborrow;

								cout << "Borrow information for book ID " << bookid << " and student ID " << studentid << " is added to the list." << endl;
							}

						}


						DisplayMenu(head);

					}

					ptr = ptr->next; 

				}
			}
		}

		else if (choice == 'R' || choice == 'r')

		{
			cout << "Enter the ID of the Student: ";

			int studentid;
			cin >> studentid;


			if (!BRExist(bookid, studentid, head)) // checking student borrowed this book or not
			{
				cout << "You have not borrowed this book!" << endl << endl;
				DisplayMenu(head);

			}

			else 

			{

				bool check = true;

				Book * ptr = head;

				BorrowInfo *ptrborrow;

				while(ptr != nullptr && check)
				{

					if (ptr->bookID == bookid)
					{
						ptrborrow = ptr->borrowInfos; 
						while(ptrborrow->next != nullptr && check)
						{
							if(ptrborrow->studentID == studentid)
							{check = false;}
							else
							{ptrborrow = ptrborrow->next;}
						}
					}
					ptr = ptr->next; 
				}
				// finding the info of the book


				cout << "Enter the return date for the book in format DD MM YYYY: ";

				int dd, mm, yyyy;
				cin >> dd;
				cin >> mm;
				cin >> yyyy;

				Date returntime (mm, dd, yyyy); 

				if (returntime < ptrborrow->borrowDate) 

				{
					cout << "Return date could not be sooner that the borrow date!" << endl << endl;
					DisplayMenu(head);
				}

				else if (returntime > ptrborrow->next->borrowDate)

				{
					cout << "Return date can not be later since there is a request for the book on "<< ptrborrow->next->borrowDate << endl << endl;
					DisplayMenu(head);
				}

				else {

					ptrborrow->returnDate = returntime;
				}

			}

		}


	}

}

void DisplayBooks(Book * head)
{
	// displaying book list

	Book * ptr = head;
	if (head == nullptr)
	{
		cout << "There is no book in the list." << endl;
		DisplayMenu(head);
	}

	else {
		cout<< "List contains:" << endl;
		while(ptr != nullptr)
		{

			cout << "Book ID: " << ptr->bookID << " Name: " << ptr->bookName <<  endl;
			ptr = ptr->next; 

		}

		DisplayMenu(head);
	}

}

void AddaBook(Book *head)
{
	// this function add a new book into library
	int bookid;
	string bookname;

	cout << "Enter the ID of a book: ";
	cin >> bookid;

	if(Exist(bookid, head))
	{
		cout << "The book is already exist in the list." << endl << endl;
		DisplayMenu(head);
	}

	else
	{

		cout << "Enter the name of the book: ";
		
		cin.ignore();
		cin.clear();
		getline(cin, bookname);

		Book *newbook = new Book;

		newbook->bookID = bookid;
		newbook->bookName = bookname;
		newbook->borrowInfos = new BorrowInfo;
		// assigning new book's values above
		Date bigdate (01, 01, 2500); // To keep this node at the end
		newbook->borrowInfos->borrowDate = bigdate;
		newbook->borrowInfos->returnDate = bigdate;
		newbook->borrowInfos->next = nullptr;
		newbook->borrowInfos->prev = nullptr;
		// assigning values of info node above, I created a node which has a big return and borrow date
		// as 01 01 2500 it is because I want that node in the end of the linkedlist to make order easier
		// I assume input is below year 2500 
		newbook->next = head;
		

		head = newbook;

		cout << "BookID " << bookid << " added to the list." << endl << endl;

		DisplayMenu(head);

	}

}

void DeleteaBook(Book * head)
{
	// Deleting wanted book function

	cout << "Enter ID of the book you want to be deleted: ";
	int bookid;
	cin >> bookid;



	if(head == nullptr)
	{
		cout << "There is no book in the list." << endl << endl;
		DisplayMenu(head);
	}


	else if (!Exist(bookid, head))

	{

		cout << "The book is not exist!" << endl << endl;
		DisplayMenu(head);

	}

	else 

	{


		{

			Book * ptr = head;

			while(ptr != nullptr)
			{
				if (ptr->bookID == bookid) // finding the book
				{

					BorrowInfo *ptrborrow = ptr->borrowInfos;

					while(ptrborrow->next != nullptr) // deleting the book's info
					{

						ptr->borrowInfos = ptrborrow->next;
						delete ptrborrow;
						ptrborrow = ptr->borrowInfos;

					}
				}


				ptr = ptr->next; 

			}

			Book * bookdel = head;
			Book * pbook; 

			bool check = true;

			if (head->bookID == bookid) // deleting the first book if it is at the head
			{
				pbook = head;
				head = head->next;
				delete pbook;
				pbook = nullptr;
				cout << "The book with ID: :" << bookid << " is successfully deleted from the list" << endl << endl;

				DisplayMenu(head);

			}

			else 

			{
				// if tobedeleted node is not at the first (below)
				Book * temp = head;

				while(bookdel != nullptr && bookdel->bookID != bookid) 
				// temp is always one node back of bookdel pointer, when bookdel shows the book with book id we delete bookdel and then temp will hold the bookdel's next node

				{
					temp = bookdel;
					bookdel = bookdel->next;

				}
				temp->next = bookdel->next;
				delete bookdel;
				bookdel = nullptr;


			}
			DisplayMenu(head);

		}

	}

}

void Terminator(Book * head)
	// Deleter function of all dynamically allocated memory
{


	Book * ptr = head;
	if (head != nullptr)
	{

		while(ptr != nullptr)
		{
			BorrowInfo *ptrborrow = ptr->borrowInfos;

			while(ptrborrow->next != nullptr) // deleting all book's circulation infos ( it is same as above function )
			{
				ptr->borrowInfos = ptrborrow->next;
				delete ptrborrow;
				ptrborrow = ptr->borrowInfos;
			}
			ptr = ptr->next; 
		}


		Book * bookdel = head;
		Book * pbook;


		if (head->next == nullptr) // again same as above function if there is only one book we delete it 
		{
			pbook = head;
			head = head->next;
			delete pbook;
			pbook = nullptr;

			cout << "All dynamically allocated memory have been return to heap " << endl << "Program Exiting..." << endl;
			exit(1);

		}

		else 

		{
			// if books more than one - temp points bookdel's next node and bookdel will point two nodes next, then the temp will be deleted
			Book * temp;
			while(bookdel->next != nullptr)
			{
				temp = bookdel->next;
				bookdel->next = temp->next;
				delete temp;
				temp = nullptr;
			} 
			delete head;
			head = nullptr;

			cout << "All dynamically allocated memory have been return to heap " << endl << "Program Exiting...";
			exit(1);

		}

	}


	exit(1);


}

void DisplayMenu(Book * head)
{
	cout <<"*******************************************************************"<< endl;
	cout <<"* Welcome to the Online Library Manager *"<< endl;
	cout <<"* Please select one option: *"<< endl;
	cout <<"* 1. Add a book *"<< endl;
	cout <<"* 2. Borrow/Return the book *"<< endl;
	cout <<"* 3. Display all previous circulation information for a book *"<< endl;
	cout <<"* 4. Delete a book *"<< endl;
	cout <<"* 5. Find all books which are previously borrowed by a student *"<< endl;
	cout <<"* 6. Find all books which are currently borrowed by a student *"<< endl;
	cout <<"* 7. Display book list *"<< endl;
	cout <<"* 8. Exit *"<< endl;
	cout <<"*******************************************************************"<< endl <<endl;


	cout << "Your choice: " ;

	int choice;
	cin >> choice;
	
	if(choice == 1)
	{
		AddaBook(head);
	}
	else if(choice == 2)
	{ 
		BorrowOrRefund(head);
	}
	else if(choice == 3)
	{	
		DisplayBookInfo(head);
		
	}
	else if(choice == 4)
	{
		DeleteaBook(head);
	}
	else if(choice == 5)
	{             
		DisplayBorrowed(head, "previously");
	}
	else if(choice == 6)
	{            
		DisplayBorrowed(head, "currently");
	}
	else if(choice == 7)
	{          
		DisplayBooks(head);
	}
	else if(choice == 8)
	{           
		Terminator(head);
	}
	else {       
		cout << "Please select a valid number from menu" << endl << endl;
		Displayer(head);
	}
	
}void Displayer (Book * head){	DisplayMenu(head);}
int main()

{
	Book * head = nullptr;

	DisplayMenu(head);


	return 0;
}