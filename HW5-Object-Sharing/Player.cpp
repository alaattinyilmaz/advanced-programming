#include <iostream>
#include "Player.h"
#include "Board.h"
#include "randgen.h"
#include <string>

using namespace std;

Player::Player(Board & board, string name) : board(board), pname(name) // Initializing
{
	point = 0;
	noMoves = 0;
}

bool Player::rollDice(){

	RandGen r; // Creating of randgen object
	diceresult = r.RandInt(1,6); // Getting a number between 1-6
	point += diceresult; // Adding result of dice into point
	noMoves++; // Increasing number of movement
	board.changeValues(diceresult); // Changing board object values
	if(board.getTotalMove() >= 15 || board.getTotalPoint() >=50) // Point and move number control
	{return false;}
	else
	{return true;}

}

void Player::display(){ // Displays dice result, player name, point and number of movement
	
	cout << "dice :" << diceresult << endl;
	cout << "Player name:" << pname << endl;
	cout << "point " << point << endl;
	cout << "Number of Moves: " << noMoves << endl << endl;

}

double Player::calculateScore() // Calculating point per movement for player
{
	return (point)/(double)noMoves;
}