// File : Proj2app.cpp
// Project : Project 2 Fall 2015
// Author : Dr. Watts
// Edited : Adrian Smith
// Description : This is the driver program for an interactive game of "Farkle".
// 		 The main function included here will accept input from
//		 the user (player) and will call the appropriate functions
//		 from the Game class.

#include <iostream>
// #include "SetLimits.h"
#include "Game.h"
using namespace std;

int main ()
{
//    SetLimits();
    char play = 'y';
    Game game ("The Dice of Fate");
    game.Instructions (cout);
    string rest;
    while (tolower (play) == 'y')
    {
	game.Init();
	while (!game.Done())
	{
		game.StartTurn();
		while (!game.TurnDone ())
		{
			cout << game << endl;
			char selection = ' ';
			cout << "Enter die letter to select or unselect a die\n";
			cout << "or enter r to save selected dice and re-roll unselected dice\n";
			cout << "or enter s to end turn and calculate score\n";
			cout << "or enter i for instructions\n";
			cout << "or enter q to quit: ";
			cin >> selection;
			while (game.Enter(tolower (selection), cout) == false)
			{
				cout << "Invalid selection; try again: ";
				getline (cin, rest);
				cin.clear();
				cin >> selection;
			}
			cout << endl;
		}
		getline (cin, rest);
		if (!game.Done())
			game.AIAPlayer (cout);
	}
	game.Message (cout);
	cout << "Would you like to play again (y/n)? ";
	cin >> play;
	cin.clear ();
    }
    cout << endl;
    return 0;
}
