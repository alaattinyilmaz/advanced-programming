#ifndef _CLASSES_H
#define _CLASSES_H
#include <iostream>
#include <string>

using namespace std;


// Base class start 
class Person
{

public:
	Person(){}
	Person(string name, int id):name(name), ID(id) {} 
	// Copy constructor for person class

	string GetName()
	// This member function returns the name
	{
		return name;
	}

	virtual void displayProfile() = 0; // Pure virtual function
	virtual int calSalary() = 0; // Pure virtual function

	virtual ~Person(){} 
	// Destructor

protected:
	string name;
	int ID;

};// Base class end
// Student class start
// This function derived from Person class
class Student: public Person
{

public:
	Student():Person(){}

	Student (string name, int id, int dorm): dormstatus(dorm), Person(name, id){}
	/*Copy Constructor for Student class which also creates a Person class object */
	virtual bool dormAccomodation()	{		bool status;		if(dormstatus==1)		{status = true;}		else 		{status = false;}		return status;	}	virtual int calSalary() = 0;
	virtual void displayProfile() = 0;
	
	virtual ~Student(){}

protected:
	int dormstatus;

};
// Student class end



// Undergraduate class start

class Undergraduate: public Student

{

public:
	Undergraduate(string name, int id, int givenyear, int dorm): year(givenyear), Student(name,id,dorm){}	/*Copy Constructor for Undergraduate class which also creates a Student object */	virtual int calSalary() { return 0; }

	virtual void displayProfile() 
	{
		cout << "Name: " << GetName() << endl;
		cout << "ID: " << ID << endl;
		cout << "Dormitory accomodation: ";

		if(dormAccomodation()==true)
		{cout << "Yes" << endl;}
		else 
		{cout << "No" << endl;}

		cout << "Year: " << year << endl;
	}

protected:
	int year;

};
// Undergraduate class end





// Graduate class start
class Graduate: public Student

{

public:	Graduate(string name, int id, int dorm, int rank, string level): scholarRank(rank), level(level), Student(name,id,dorm){}	/*Copy Constructor for Graduate class which also creates a Student object */	virtual int calSalary()
	{

		int salary = ((scholarRank-1)*1250);

		if(level == "phd")
		{
			salary += 600;
		}
		else if (level == "master")
		{
			salary += 500;
		}

		return salary;
	}

	virtual void displayProfile() 
	{
		cout << "Name: " << GetName() << endl;
		cout << "ID: " << ID << endl;
		cout << "Dormitory accomodation: ";

		if(dormAccomodation()==true)
		{cout << "Yes" << endl;}
		else {cout << "No" << endl;}

		cout << "Scholarship rank: " << scholarRank << endl;
	}


protected:
	int scholarRank;
	string level;

};
// Graduate class end



// Employee class start
class Employee: public Person
{

public:
	Employee(): Person(){}	Employee(string name, int id, string department): department(department), Person(name,id){}	/*Copy Constructor for Employee class which also creates a Person class object */	virtual int calSalary() = 0;
	virtual void displayProfile() = 0;
	
	virtual ~Employee(){}

protected:
	string department;

};
// Employee class end



// Staff class start
class Staff: public Employee
{

public:
	Staff(): Employee(){}	Staff(string name, int id, int position, int workdays, string department): position(position), daysOfWork(workdays), Employee(name,id,department){}	/*Copy Constructor for Staff class which also creates a Employee class object */	virtual int calSalary()
	{

		return (40*daysOfWork*position);
	}


	virtual void displayProfile() 
	{
		cout << "Name: " << GetName() << endl;
		cout << "ID: " << ID << endl;
		cout << "Department: " << department << endl;
		cout << "Position: " << position << endl;
		cout << "Days of work: " << daysOfWork << endl;
	}

protected:
	int position;
	int daysOfWork;

};
// Staff class end



// FacultyMember class start
class FacultyMember: public	Employee

{

public:	FacultyMember(): Employee(){}	FacultyMember(string name, int id, int classnum, int office, int rank, string department): rank(rank), classestaught(classnum), officeHours(office), Employee(name,id,department){}	/*Copy Constructor for FacultyMember class which also creates a student object */	virtual int calSalary()
	{
		int salary = classestaught*2000 + officeHours * 100 + rank*1000;
		return salary;
	}


	virtual void displayProfile() 
	{
		cout << "Name: " << GetName() << endl;
		cout << "ID: " << ID << endl;
		cout << "Department: " << department << endl;
		cout << "Office Hours: " << officeHours << endl;
		cout << "# of classes taught: " << classestaught << endl;
		cout << "Rank: " << rank << endl;
	}


protected:
	int classestaught;
	int officeHours;
	int rank;

};
// Faculty member class end


#endif