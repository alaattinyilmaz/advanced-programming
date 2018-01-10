#ifndef _PLAYER_H
#define _PLAYER_H
#include "Board.h"

using namespace std;

class Player
{
public:
	Player(Board &,string); // Initializes the values 
	bool rollDice(); // Creates a number between 1-6 and make changes on board object 
	void display();  // Displays dice result, player name, point and number of movement
	double calculateScore(); // Calculates point per movement for player

private:
	Board & board; // We take board object as referance because we want to share one certain board with players
	int point;
	int noMoves;
	int diceresult;
	string pname;
};

#endif