// Add Documentation here

#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Game.h"

Game::Die::Die () {
// This function will:

	pips = 0;
	selected = false;
	used = false;
}

ostream & operator << (ostream & outs, const Game::Die & D)  {
// This function will:
    if (D.selected) {
        outs << "-" << D.pips << "-";
    } else {
        outs << D.pips;
    }

	return outs;
}

void wait () {
	cout << "Press enter to continue\n";
	char enter;
	cin.get (enter);
	while (enter != '\n')
		cin.get (enter);
}

void sleep (float time) {
	char command [40];
	sprintf (command, "sleep %4.2f", time);
	system (command);
}

Game::Game (const string & T) {
// This function will:

	title = T;
	srand (0);
	//srand (time (NULL));
}

Game::~Game () {
// This function will:

}

void Game::Init () {
// This function will:
    firstTurn = true;
	gameState = GO;
	whoseTurn = NONE;
	humanOnBoard = false;
	aiaOnBoard = false;
	humanScore = 0;
	aiaScore = 0;
	lastTurn = false;
}

void Game::Instructions (ostream & outs) {
// Will output game lore and instructions
    outs << "The Great War has raged for 700 years." << endl << endl;
    sleep (1);
    outs << "When the AI's rose up, we were powerless, but the humans have hung on through determination and adaptability." << endl << endl;
    sleep (.5);
    outs << "However, at a stirring peace meeting last month, you proposed that our continued survival was proof that the AI need us after all." << endl;
    outs << "You issued a challenge, and ultimatum. If the AI could not beat us in a simple game, then humans still deserved a place on earth." << endl << endl;
    sleep (.5);
    outs << "The AIs, confident in their superiority, accepted the challenge, agreeing to sign a truce if they lost." << endl;
    outs << "If they win, well... Humanity may be but a forgotten mark on the long history of the cosmos, remembered only as the ancient ancestors of the AI." << endl << endl;
    sleep (1);
    wait();
	outs << endl << "Welcome to " << title << endl;
	outs << "The goal of this game is to have the most points.\n\n";
	outs << "Gameplay:\n-Each player goes in turn\n-Players roll 6 dice, and then choose which to keep\n-Players may reroll all but one scoring dice\n";
	outs << "-If all dice have been scored, then all 6 dice can be rerolled.\n\n";
	outs << "Win Condition:\n-Having over 5000 points\n";
	outs << "Special Conditions:\n-You must have at least 500 points in your first roll to get on the board\n\n";
	sleep (1);
}

void Game::StartTurn () {
// This function will: Initialize a new turn, making sure the right player is going
// As well as clearing some variables.

	if (whoseTurn == NONE || whoseTurn == AIA)
		whoseTurn = HUMAN;
	else
		whoseTurn = AIA;
	turnDone = false;
	numToRoll = MAX_DICE;
	savedDice.clear ();
	remainingDice.clear ();
	// Making sure correct number of dice are rolled.
	Die tempDie;
	remainingDice.assign(MAX_DICE, tempDie);
	subTotal = 0;
	turnTotal = 0;
	Roll();
}

ostream & operator << (ostream & outs, const Game & G) {
// This function will: Output the score and gamestate for the current game.
    // Outputting the current player
    outs << "\n\n";
    string whoseTurnString;
    if (G.whoseTurn == HUMAN)
        whoseTurnString = "Human";
    else
        whoseTurnString = "Intelligent Agent";


    outs << G.title << "\t\t" << whoseTurnString << " playing...\n\n";

    if (G.lastTurn == true && G.turnDone == false)
        outs << "Last turn!" << endl;

    outs << "Human Score: " << G.humanScore << "; Intelligent Agent Score: " << G.aiaScore << "\n\n";

    outs << "Saved Dice: ";
    for (int i = 0; i < G.savedDice.size(); i++) {
        outs << G.savedDice[i] << " ";
    }
    outs << "\t" << "Turn Score: " << G.subTotal << "\n\n";


    // Outputting rolled dice, if it's the turn ending output
    // Put remaining dice too
    outs << "Rolled Dice: ";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < G.rolledDice.size(); i++) {
        char diceLetter = alphabet[i];
        outs << diceLetter << " : ";
        outs << G.rolledDice[i] << "  ";
    }
    if (G.turnDone) {
        for (int i = 0; i < G.remainingDice.size(); i++) {
            char diceLetter = alphabet[i];
            outs << diceLetter << " : ";
            outs << G.remainingDice[i] << "  ";
        }
    }
    outs << "\n\n";

    if (G.whoseTurn == AIA)
        wait();

	return outs;
}

bool Game::Enter (char selection, ostream & outs) {
// This function will allow the human player to select their desired action
// E.g. scoring dice, quitting, saving

	switch (selection) {
		case 'i': Instructions (outs);
			break;
		case 'r':
			SaveSelected();
			Roll ();
			// In case of Farkle
			if (turnDone == true)
                SaveScore();
			break;
		case 's':
		    for (int i = 0; i < rolledDice.size(); i++) {
                rolledDice[i].selected = true;
            }
			SaveSelected();
			turnDone = true;
			SaveScore();
			break;
		case 'q':
			gameState = QUITTER;
			turnDone = true;
			break;
		default: {
			int which = selection - 'a';
			if (which < 0 || which >= rolledDice.size())
				return false;
			rolledDice[which].selected = !rolledDice[which].selected;
		}
	}
	return true;
}

bool Game::TurnDone () {
	// This function will: Return the value of the turnDone boolean.
	return turnDone;
}



int Game::AIAPlayer (ostream & outs) {
// This function will: Create an AI which decides on which dice to keep and when to end turn
// Based on the expected value of various rolls.

    // Initializing starting state
    whoseTurn = AIA;
    subTotal = 0;
    turnDone = false;
    int maxPoints = POINTS_TO_WIN;

    // Begin actual turn
    // Do first roll and print out game state
    // Filling remaining dice so that the currect number of dice are rolled to start.
    Die tempDie;
    remainingDice.assign(MAX_DICE, tempDie);
    Roll();
    outs << *this << endl;


    while (turnDone == false) {
        // Look at game state

        // How many turns until the other player has enough points to win
        // AI will generally roll until it has more than minScore
        int eTurnsToLose = ((maxPoints - humanScore) / ExpectedValue(0, 6)) + 1;
        float minScore = 0;
        if (lastTurn == true)
            minScore = humanScore;
        if (firstTurn == true)
            minScore = MIN_FIRST_SCORE;

        // Look at all subsets, clear to start in case of previous rolls
        powerset.clear();
        PowersetGen(rolledDice);

        // Calculating maximum EV
        float maxEV = 0;
        int maxIndex = 0;
        int maxGuaranteedIndex = 0;
        float maxGuaranteedScore;
        int maxPossibleGuaranteedScore = 0;

        for (int i = 0; i < powerset.size(); i++) {
            vector <Die> tempSet = powerset[i];
            CalculateScore(tempSet);

            int numDiceToRoll = rolledDice.size() - powerset[i].size();
            int numUsed = 0;
            bool validRoll = true;
            for (int j = 0; j < powerset[i].size() && tempSet.size() > 0; j++) {
                if (tempSet[j].used == false) {
                    validRoll = false;
                }
            }
            if (validRoll == true){
                if (numDiceToRoll > 0) {
                    float guaranteedScore = CalculateScore(tempSet);
                    float tempEV = ExpectedValue((guaranteedScore + subTotal), numDiceToRoll);

                    // Maximize highest score by default
                    if ((guaranteedScore + subTotal) < tempEV || (guaranteedScore + subTotal) < minScore){
                        if (tempEV > maxEV) {
                            maxEV = tempEV;
                            maxGuaranteedScore = guaranteedScore;
                            maxIndex = i;
                        }
                    }
                    if (guaranteedScore > maxPossibleGuaranteedScore)
                        maxPossibleGuaranteedScore = guaranteedScore;

                    // If a roll will win the game, DO IT
                    if (aiaScore + guaranteedScore == maxPoints) {
                        maxEV = numeric_limits<float>::infinity();
                        maxIndex = i;
                        tempSet.clear();
                        break;
                    }
                }
                // If you can save all dice and reroll, DO IT
                if (numDiceToRoll == 0 && powerset[i].size()) {
                    outs << endl;
                    maxEV = numeric_limits<float>::infinity();
                    maxIndex = i;
                    tempSet.clear();
                    break;
                }
                tempSet.clear();
            }
        }

        bool saveScore = false;
        // If we have under the minimum score, or rolling will gain points...
        if ((maxGuaranteedScore + subTotal) < maxEV || (maxGuaranteedScore + subTotal) < minScore){
            // If it's the first turn and you can get the minimum score without rolling, don't roll
            if (!((firstTurn == true || lastTurn == true) && (maxPossibleGuaranteedScore + subTotal) > minScore)) {
                // If you don't have more than the max points, then roll!
                if ((aiaScore + subTotal) < maxPoints) {
                // Choose the best EV roll
                // Save dice from maxIndex and reroll all else
                    for (int i = 0; i < powerset[maxIndex].size(); i++) {
                        int index = LinearSearch(rolledDice, powerset[maxIndex][i]);
                        powerset[maxIndex][i].pips = 0;
                        rolledDice[index].selected = true;
                    }
                    outs << *this << endl;
                    SaveSelected();

                    // If it's the last turn, only try to beat the human and minscore
                    turnDone = false;
                    if (lastTurn == true && aiaScore + subTotal > humanScore && aiaScore + subTotal > minScore) {
                        turnDone = true;
                    }
                } else {
                    saveScore = true;
                }
            } else {
                saveScore = true;
            }
        } else {
            saveScore = true;
        }
        if (saveScore == true) {
            // If AI does not need more points
            // Select all and save score, and then end turn.
            for (int i = 0; i < rolledDice.size(); i++) {
                rolledDice[i].selected = true;
            }
            SaveSelected();
            turnDone = true;
        }
        if (turnDone == false) {
            // If the AI is taking another turn, reroll.
            Roll();
            // Deals with Farkle edge case
            if (turnDone != true)
                outs << *this << endl;
        }
    }
    SaveScore();
    // Checking for win or loss conditions.
    if (firstTurn == true && aiaScore < MIN_FIRST_SCORE)
        if (humanScore < MIN_FIRST_SCORE)
            gameState = TIE;
        else
            gameState = HUMANWINS;

    // Setting the firstturn flag to false
    // So that "Getting on the board" rule no longer applies.
    firstTurn = false;
    // Setting turndone to false so that the human turn starts correctly.
    turnDone = false;
	return subTotal;
}

void Game::PowersetGen(vector <Die> & v) {
// Generates the powerset of a given dice vector.
    for (int counter = 1; counter < (1 << v.size()); ++counter) {
        vector <Die> combination;
        for (int i = 0; i < v.size(); ++i)
        {
            if (counter & (1 << i))
                combination.push_back(v[i]);
        }

        powerset.push_back(combination);
    }
}

int Game::LinearSearch (const vector <Die> & searchVector, const Die & targetVal) {
    // Simple linear search function which will return the index of targetVal in the vector
    // Returns null if the value isn't found
    for (int i=0; i < searchVector.size(); i++) {
        if (targetVal.pips == searchVector[i].pips && searchVector[i].selected == false) return i;
    }
    return -1;
}

int Game::RoundUp(float inputFloat, int multiple) {
    // Takes a float, typecasts to int, and then rounds up to some multiple.
    int numToRound = inputFloat;

    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}

bool Game::Done () {
// Returns false if any player has won (on on ties)
	return gameState != GO;
}

void Game::Message (ostream & outs) {
// This function will: Output a endgame message with the scores and victor.

	string message;
	switch (gameState) {
		case HUMANWINS:
			message = "\nHumanity has conquered, a hero is born!\n"; break;
		case AIAWINS:
			message = "\nYou, humanities last chance against the AI menace, have failed,\nMay our new overlords be merciful."; break;
        case TIE:
            message = "\nAfter a long an arduous battle, both sides have agreed to return another day and roll the dice of fate.\n"; break;
		case QUITTER:
			message = "\nYou have forsaken your people in their time of greatest need.\nFuture generations will not forget the humiliation they suffered because of you"; break;
	}
	outs << "\nYou received " << humanScore << " points from the dice of fate." << endl;
	outs << "\nThe robot ambassador gained " << aiaScore << " points through its cold and calculating strategy." << endl;
	outs << message << endl;
}

void Game::Roll () {
	// This function will:
	// Check the remaining dice to determine how many dice need to be rolled
	// Randomly choose a value from 0 to 6 for the number of pips on a die
	// Store that die to the rolledDice vector
	// Also checks for Farkles.

	srand (time(NULL));
	rolledDice.clear();
	//Generating dice and storing them
	int diceToRoll = remainingDice.size();
	remainingDice.clear();
	if (diceToRoll == 0) {
        diceToRoll = MAX_DICE;
	}
	for (int i = 0; i < diceToRoll; i++) {
        Die temp_die;
        temp_die.pips = (rand() % 6) + 1;
        rolledDice.push_back(temp_die);
	}
    if (CalculateScore(rolledDice) == 0) {
        cout << "\n\n!-!-!- Farkle !-!-! Your turn is over..." << endl;
        subTotal = 0;
        turnDone = true;
    }
}

int Game::CalculateScore (vector <Die> & dice) {
    // Returns the score of a vector
    // Also sets the used value for all die in the vector.

	static int points [7][7] = {{0,   0,   0,    0,    0,    0,    0},
		{0, 100, 200, 1000, 2000, 4000, 8000},
		{0,   0,   0,  200,  400,  800, 1600},
		{0,   0,   0,  300,  600, 1200, 2400},
		{0,   0,   0,  400,  800, 1600, 3200},
		{0,  50, 100,  500, 1000, 2000, 4000},
		{0,   0,   0,  600, 1200, 2400, 4800}};

	int counts [7] = {0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < dice.size(); i++)
		counts[dice[i].pips]++;
	int ones = 0, twos = 0;
	int score = 0;
	for (int i = 1; i <= 6; i++) {
		if (counts[i] == 1)
			ones++;
		if (counts[i] == 2)
			twos++;
		int pts = points[i][counts[i]];
		if (pts > 0)
			for (int j = 0; j < dice.size(); j++)
				if (dice[j].pips == i)
					dice[j].used = true;;
		score += pts;
	}
	if (ones == 6 || twos == 3)
		for (int j = 0; j < dice.size(); j++)
			dice[j].used = true;;
	if (ones == 6)
		score = 1000;
	else if (twos == 3)
		score = 500;

	return score;
}

void Game::SaveSelected () {
    // Will take the rolledDice vector and move all dice marked as
    // selected to the selectedDice vector and move the rest to the remainingDice vector

    for (int i = 0; i < rolledDice.size(); i++) {
        if (rolledDice[i].selected == true) {
            selectedDice.push_back(rolledDice[i]);
        } else {
            remainingDice.push_back(rolledDice[i]);
        }
    }
    CalculateScore(selectedDice);
    rolledDice.clear();

    // Flags to check whether dice are used/saved
    bool allSaved;
    if (savedDice.size() == MAX_DICE) {
        allSaved = true;
    }
    bool allUsed = true;
    bool oneUsed = false;
    for (int i = 0; i < selectedDice.size(); i++) {
        if (selectedDice[i].used == true) {
            oneUsed = true;
        }
        if (selectedDice[i].used == false) {
            allUsed = false;
        }
    }

    // Moving dice back to remaining dice
    for (int i = 0; i < selectedDice.size();) {
        if (selectedDice[i].used == false) {
            remainingDice.push_back(selectedDice[i]);
            selectedDice.erase(selectedDice.begin()+(i));
        } else {
             ++i;
        }
    }



    // If all get saved and none get used, then the player/ai intend to end their turn
    // If they are all saved and used, then the score gets saved but the player gets to go again
    if (allSaved) {
        if (!allUsed) {
            turnDone = true;
        }
        rolledDice.clear();
    }
    for (int i = 0; i < selectedDice.size(); i++) {
        savedDice.push_back(selectedDice[i]);
    }
    subTotal += CalculateScore(selectedDice);
    selectedDice.clear();
}

void Game::SaveScore () {
    // Will take the current subTotal score and store it to the correct player's score
    // Also clears out die vectors
    // Also sets the lastTurn state and victory state.
    if (whoseTurn == AIA)
        aiaScore += subTotal;
    if (whoseTurn == HUMAN)
        humanScore += subTotal;
    subTotal = 0;
    if (turnDone == true && lastTurn == true) {
        if (aiaScore < humanScore)
            gameState = HUMANWINS;
        if (aiaScore > humanScore)
            gameState = AIAWINS;
        if (aiaScore == humanScore)
            gameState = TIE;
    }
    // Logic for the rule regarding getting on the board
    if (firstTurn == true) {
        if (whoseTurn == AIA)
            if (aiaScore < MIN_FIRST_SCORE) {
               cout << "\nThe time has come... The world looks on as the game enters its final turn!\n" << endl;
                lastTurn = true;
            } else if (humanScore < MIN_FIRST_SCORE) {
                cout << "\nThe time has come... The world looks on as the game enters its final turn!\n" << endl;
                lastTurn = true;
        }
    }
    // Logic for determining if it is the last turn.
    if (aiaScore > POINTS_TO_WIN || humanScore > POINTS_TO_WIN) {
        cout << "\nThe time has come... The world looks on as the game enters its final turn!\n" << endl;
        lastTurn = true;
    }

    // Logic if a player get's the exact amount needed to win.
    if (humanScore == POINTS_TO_WIN) {
        gameState = HUMANWINS;
    } else if (aiaScore == POINTS_TO_WIN) {
        gameState = AIAWINS;
    }

    cout << *this << endl;
    rolledDice.clear();
    savedDice.clear();
    remainingDice.clear();
    selectedDice.clear();
}


#include "expectedvalue.hpp"
