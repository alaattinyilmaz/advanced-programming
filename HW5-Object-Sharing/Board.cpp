#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() : totalPoint(0), totalMove(0) // Initializing 
{}

void Board::display() // Displays total points and total number of movements
{
	cout << "Total points: " << totalPoint << endl;
	cout << "Total moves: " << totalMove << endl;
}

void Board::changeValues(const int & diceresult) // Increases total point with dice result and increasing movement number
{
	totalMove++;
	totalPoint+=diceresult;
}

int Board::getTotalPoint() // Returns the total point
{
	return totalPoint;
}

int Board::getTotalMove() // Returns the total number of movement
{
	return totalMove;
}