#ifndef _BOARD_H
#define _BOARD_H

class Board
{

public:
	Board(); // Constructer
	void display(); // Displays total points and total number of movements
	void changeValues(const int &); // Changes values of move number and points
	int getTotalPoint(); // Returns total point
	int getTotalMove(); // Returns total number of movement

private:
	int totalPoint;
	int totalMove;
};

#endif