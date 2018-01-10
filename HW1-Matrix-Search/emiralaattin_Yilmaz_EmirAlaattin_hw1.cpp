/*
EMÝR ALAATTÝN YILMAZ 
19705
This program counts the number of distinct letters in valid sub-matrices of an input matrix and output the number and the letters themselves.
*/

#include <iostream>
#include <fstream>      
#include <cctype>        // Libary to use tolower() function
#include <string>
#include <vector>

using namespace std;

void SortVector(vector <char> & vector)
	// Insertion Sort Algorithm from CS201 Lecture Notes
{
	int k,loc, numElts = vector.size();
	for(k=1; k < numElts; k++) 
	{   char hold = vector[k];  
	loc = k;             
	while (0 < loc  && hold < vector[loc-1])
	{   vector[loc] = vector[loc-1];
	loc--;
	}
	vector[loc] = hold;
	}
}


bool Exist (vector<vector<char>> & matrix, int rows, int cols)	
	// Checker function to understand whether an element is in a matrix 
{

	for (unsigned int j = 0 ; j < matrix.size(); j++)
	{   
		for (unsigned int k = 0 ; k < matrix[0].size(); k++) // It is checking the previous elements
		{   

			if ((rows == j && cols ==k)) // Stops when it comes to position of elements
			{ return false; }

			else if(matrix[rows][cols] == matrix[j][k]) // Returns true when it finds a duplicated one
			{ return true; }

		}

	}

	return false;
}


void distinctCountandPrint(vector<vector<char>> & matrix)
	// This function counts and prints distinct elements in a matrix and it assigns these distinct elements into a vector: 'distinctchars'
{
	vector <char> distinctchars;
	int distinctcount = 0;

	// Checking all the elements in the matrix
	for (unsigned int i = 0; i < matrix.size(); i++)
	{
		for (unsigned int j = 0; j < matrix[0].size(); j++)
		{
			if(!Exist(matrix, i, j)) // If it doesn't exist in this matrix before it counts this char as distinct letter
			{
				distinctchars.push_back(matrix[i][j]); // And it adds this char into letters vector
				distinctcount++;
			}
		}
	}

	cout << distinctcount << ":"; // Number of distinct chars

	SortVector(distinctchars); // Sorting distinctchars vector in lexicographical order

	for (unsigned int i = 0; i < distinctchars.size(); i++) // Printing elements
	{ cout << distinctchars[i]; } 

}

int main()

{

	ifstream inputmatrix;
	string filename;
	cout << "Enter the name of the file" << endl;
	cin >> filename;

	inputmatrix.open(filename.c_str());

	if (inputmatrix.fail())
	{
		cout << "File couldn't open." << endl;
		return 0;
	}

	string line; 
	char ch;

	int linecount = 0;
	int charcount;
	int temp = 0;


	while(getline(inputmatrix, line)) // Gets the lines of input file

	{
		charcount = 0;
		for (unsigned int i = 0; i < line.length(); i++)
		{
			ch = line.at(i);
			if (ch != ' ') // Ignoring blanks in line
			{
				if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) // Checking whether it is a letter
				{
					cout << "Error: Matrix contains invalid letter: " << ch << endl;
					cout << "Program Exiting..." << endl;
					return 0;
				}

				else 
				{ charcount++; } // Counting of chars in this line 
			}
		}

		linecount++; // Counting of lines

		if (charcount != temp && linecount > 1) // Comparing char counts with the number of chars of previous line
		{
			cout << "Error: number of element in each rows are not same" << endl;
			cout << "Program Exiting..." << endl;
			return 0;
		}


		temp = charcount;

	}

	int rows = linecount;
	int cols = charcount;

	vector<vector<char>> matrix(rows);

	inputmatrix.clear();
	inputmatrix.seekg(0); // Reading the input file from top

	for (int i = 0; i < rows; i++)

	{

		getline(inputmatrix, line);

		for (unsigned int j=0; j < line.length(); j++)
		{
			ch = tolower(line.at(j)); // Setting uppercases to lowercases
			if (ch != ' ') // Checking blank
			{
				matrix[i].push_back(ch); // Adding this element into matrix
			}
		}
	}

	for (int i = 0; i < rows; i++) // Row coordinate of top-left element of matrix
	{
		for (int j = 0; j < cols; j++) // Column coordinate of top-left element of matrix
		{
			for (int k = 1; i + k <= rows; k++) // Rows of Submatrix 
			{
				for (int t = 1; j + t <= cols; t++) // Columns of Submatrix
				{
					vector<vector<char>> submatrix(k, vector<char>(t)); // Creating a matrix with k(rows) × t(columns) sizes
					int z = i; // Row Coordinate of the element in main matrix which we will assign into submatrix
					for (int a = 0; a < k || z <= k-1; a++) // Getting rows of created submatrix
					{
						int v = j;  // Column Coordinate of the element in main matrix which we will assign into submatrix
						for (int b = 0; b < t || v <= t-1; b++) // Getting columns of created submatrix
						{
							submatrix[a][b] = (matrix[z][v]); // Assigning elements into submatrix
							v++;
						}
						z++;
					}

					cout << "((" << i+1 << "," << j+1 << ")," << k << "," << t << "):";
					distinctCountandPrint(submatrix);
					cout << endl;
				}

			}
		}

	}

	return 0;
}