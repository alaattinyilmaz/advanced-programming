#include <iostream>
#include <string>
#include "DynStack.h"
#include "DynQ.h"

using namespace std;

bool checkOne(string sequence) // This function checks first condition
{

	if(sequence.length() % 2 != 0) // Checking the length of sequence if there are couples or not
	{return false;}

	else 
	{
		DynStack lowstack;
		char ch, low;
		int lowcounter = 0;
		int upcounter = 0;

		for(unsigned int i = 0; i < sequence.length(); i++) // if it is lower case
		{
			ch = sequence.at(i);
			if(ch >= 'a' && ch <= 'z')
			{
			lowstack.push(ch); // Add this lower case to stack
			lowcounter++; // counting of lower cases
			}
			else if (ch >= 'A' && ch <= 'Z') // if it is upper case
			{
				upcounter++; // counting of upper cases
				if(!lowstack.IsEmpty())
				{
					lowstack.pop(low);
					if(low != ch - ('A'-'a')) // Checking this element with the upper case it needs to be same
					{
						return false;
					}
				}
			}
		}

		if (!lowstack.IsEmpty())// This line prevents if user begins with upper cases, because if it begins with upper cases it can not decrease the number of lower case stack
		{return false;}

		else if (lowcounter == upcounter) // Checking if lower cases equal to upper cases
		{return true;}

		else
		{return false;}
	}
}

bool checkTwo(string sequence) // This function checks the second condition
{
	if(sequence.length() % 2 != 0) // Checking the length of sequence if there are couples or not
	{return false;}

	else 
	{
		DynQ lowQ;
		char ch, low;
		int lowcounter = 0;
		int upcounter = 0;

		for(unsigned int i = 0; i < sequence.length(); i++)
		{
			ch = sequence.at(i);
			if(ch >= 'a' && ch <= 'z') // if it is lower case 
			{
				lowQ.qadd(ch); // Add this lower case to queue
				lowcounter++; // counting of lower cases
			}

			else if (ch >= 'A' && ch <= 'Z') // if it is upper case
			{
				upcounter++; // counting of upper cases
				if(!lowQ.IsEmpty())
				{
					lowQ.qdrop(low); // First element of lower case queue 
					if(low != ch - ('A'-'a')) // Checking this element with the upper case it needs to be same
					{return false;}
				}
			}
		}
		if(!lowQ.IsEmpty()) // This line prevents if user begins with upper cases, because if it begins with upper cases it can not decrease the number of lower case queue
		{return false;}
		else if (lowcounter == upcounter) // Checking if lower cases equal to upper cases
		{return true;}

		else
		{return false;}
	}

}

int main()

{
	string sequence;
	string choice;

	do 
	{
		cout << "Please choose which sequence format are you going to search ? First or Second: ";
		cin >> choice;

		if (choice=="1")
		{
			cout << "Enter a sequence: ";
			cin >> sequence;
			if (checkOne(sequence))
			{cout << "The input is in correct format" << endl;}
			else 
			{cout << "invalid format" << endl;}
		}
		else if(choice=="2")
		{
			cout << "Enter a sequence: ";
			cin >> sequence;

			if (checkTwo(sequence))
			{cout << "The input is in correct format" << endl;}
			else 
			{cout << "invalid format" << endl;}

		}
		else
		{cout << "You entered invalid input" << endl;}
	}

	while (cin);

}