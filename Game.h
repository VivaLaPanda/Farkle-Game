// Add Documentation here

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

#define MAX_DICE 6
#define POINTS_TO_WIN 5000
#define MIN_FIRST_SCORE 500

enum state_types { GO, HUMANWINS, AIAWINS, TIE, QUITTER };
enum player_type { NONE, HUMAN, AIA };

class Game
{
    public:
        Game (const string & T);
        ~Game ();
	void Init ();
    void Instructions (ostream & outs);
	void StartTurn ();
	friend ostream & operator << (ostream & outs, const Game & G);
    bool Enter (char selection, ostream & outs);
	bool TurnDone ();
	int AIAPlayer (ostream & outs);
	bool Done ();
    void Message (ostream & outs);

	struct Die
	{
		Die ();
		friend ostream & operator << (ostream & outs, const Die & D);
		int pips = 0;
		bool selected = false;
		bool used = false;
	};

    private:
        void Roll ();
	int CalculateScore (vector <Die> & dice);
	void PowersetGen(vector <Die> & v);
	void SaveSelected ();
	void SaveScore ();
	float ExpectedValue (float tempScore, int numDiceToRoll);
	int LinearSearch (const vector <Die> & searchVector, const Die & targetVal);
	int RoundUp (float numToRound, int multiple);
	void PipsToVector (vector <Die> & outputVector, vector <int> & pipsVector);

	string title;
        vector <Die> rolledDice;
        vector <Die> remainingDice;
        vector <Die> selectedDice;
        vector <Die> savedDice;
        vector <vector <Die> > powerset;
	state_types gameState;
	player_type whoseTurn;
	bool firstTurn;
	bool turnDone;
	bool aiEndTurn;
	int numToRoll;
	int rolledScore;
	int subTotal;
	int turnTotal;
	bool humanOnBoard;
	bool aiaOnBoard;
	int humanScore;
	int aiaScore;
	bool lastTurn;
};

#endif
