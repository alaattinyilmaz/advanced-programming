#include <iostream>
#include "Classes.h"

using namespace std;

Person * getPerson() 
// Person pointer function which dedicates the person 
{
	int choice;
	string name;
	int id;

	cout << "Choose an option (1,2,3, or 4):" << endl << 
			"1. undergraduate student " << endl << 
			"2. graduate student" << endl <<
			"3. staff" << endl << 
			"4. faculty member" << endl; 

	cin >> choice;
	
	if(choice == 1)
	{
	cout << "You chose undergraduate. Give person's name, id, accommodation status (1 for yes and 0 for no), and year:" << endl;
	
	cin >> name;
	cin >> id;
	
	int dorm, year;
	
	cin >> dorm;
	cin >> year;
	
	Undergraduate * undergrad = new Undergraduate(name, id, year, dorm);
	// Allocating memory from heap to create an undergraduate student object

	return undergrad;

	}

	else if(choice == 2)
	{
	cout << "You chose graduate. Give person's name, id, accommodation status (1 for yes and 0 for no),scholar Rank(btw 1 and 3) and level(phd or master):" << endl;
	
	cin >> name;
	cin >> id;
	
	int dorm, rank;
	string level;
	
	cin >> dorm;
	cin >> rank;
	cin >> level;
	
	Graduate * grad = new Graduate(name, id, dorm, rank, level);
	// Allocating memory from heap to create an graduate student object

	return grad;

	}
	
	else if(choice == 3)
	{
	cout << "You chose staff. Give person's name, id, department, position(btw 1 and 4) and Days of work:" << endl;
	
	cin >> name;
	cin >> id;
	
	string department;
	int position, workdays;

	cin >> department;
	cin >> position;
	cin >> workdays;
	
	Staff * staffperson = new Staff(name, id, position,workdays, department);
	// Allocating memory from heap to create an staff employee object

	return staffperson;

	}
	
	else if(choice == 4)
	{
	cout << "You chose faculty member. Give person's name, id, department, number of classes taught,officehours, and rank(btw 1 and 4):" << endl;
	
	cin >> name;
	cin >> id;
	
	string department;
	int classnum, office, rank;
	
	cin >> department;
	cin >> classnum;
	cin >> office;
	cin >> rank;

	FacultyMember * facultyperson = new FacultyMember(name, id, classnum, office, rank, department);
	// Allocating memory from heap to create a faculty member

	return facultyperson;

	}

}


int main()

{

	cout<<"WELCOME TO THE PERSON PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	Person * person_1; /* define person_1 of the class person.*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Getting person "<<endl;
		person_1 = getPerson(); // Getting the person
		cout<<"********************************************************************"<<endl<<endl;
	    cout<<"The profile of a person:"<<endl;
		person_1->displayProfile(); // Displaying profile of the person
		cout<<"Salary: "<<person_1->calSalary()<<endl;
		
		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
      cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
	  
	  delete person_1; // Deleting allocated memory from heap
	}
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
    system("pause");
    return 0;



	
}