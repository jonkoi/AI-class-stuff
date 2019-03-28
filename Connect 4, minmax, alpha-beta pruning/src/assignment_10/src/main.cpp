#include<Players.hpp>
#include<GameBoard.hpp>
#include<iostream>
#include<string>
#include<climits>

void playGame()
{
	const int MAX_FIELD_SIZE = 10;
	const int MAX_AI_DEPTH = 10;
	string inputString;

	// initialize players and board from user input:
	int width
	{ 0 }, height
	{ 0 };
	do
	{
		cout << "Specify board width (0-10): ";
		cin >> inputString;
		width = (int) inputString[0] - 48;
	} while (!(width > 0 && width <= MAX_FIELD_SIZE));
	cout << "\n";
	do
	{
		cout << "Specify board height (0-10): ";
		cin >> inputString;
		height = (int) inputString[0] - 48;
	} while (!(height > 0 && height <= MAX_FIELD_SIZE));
	cout << "\n";

	GameBoard fourGame = GameBoard(width, height);

	int pruning
	{ 0 };
	do
	{
		cout << "Enable alpha-beta-pruning for AI-Player? (0 = no, 1 = yes): ";
		cin >> inputString;
		pruning = (int) inputString[0] - 48;
	} while (!(pruning == 0 || pruning == 1));
	cout << "\n";

	int depth
	{ 0 };
	do
	{
		cout << "Set AI search depth: ";
		cin >> inputString;
		depth = (int) inputString[0] - 48;
	} while (!(pruning == 0 || pruning == 1));
	cout << "\n";

	const bool isMaxPlayer = true;
	ComputerPlayer maxPlayerX = ComputerPlayer(&fourGame, isMaxPlayer,
			(bool) pruning, depth);
	HumanPlayer minPlayerO = HumanPlayer(&fourGame, !isMaxPlayer);

	// game begins here:
	bool maxPlayersTurn = true; // this could be randomized.

	int turn = 0;
	while (fourGame.getUtility() != INT_MAX && fourGame.getUtility() != INT_MIN
			&& !fourGame.isFieldFull())
	{
		turn++;
		cout << "\n";
		cout << " ---------- Turn Number " << turn << " -----------" << endl;
		int move;

		if (maxPlayersTurn)
			move = maxPlayerX.makeMove();
		else
			move = minPlayerO.makeMove();

		if (maxPlayersTurn)
			cout << "MaxPlayer chose column: " << move << "\n";
		else
			cout << "MinPlayer chose column: " << move << "\n";

		fourGame.printField();

		cout << "Utility of current field: " << fourGame.getUtility() << "\n";

		//Just to know...
		//cout << "Min/Max possible utiliy = " << INT_MIN << " / " << INT_MAX << "\n";

		maxPlayersTurn = !maxPlayersTurn;
	}
	int utility = fourGame.getUtility();
	if (fourGame.isFieldFull() && (utility == 0))
	{
		cout << "Draw!" << "\n";
	}
	else
	{
		if (utility == INT_MAX)
			cout << "Max Player won, congratulations";
		else if (utility == INT_MIN)
			cout << "Min Player won, congratulations";
		else
			cout << "ERROR: This should never be printed";
	}
}

void debugGame()
{
	// Perhaps you want to try out things.
	// In that case, comment playGame() in main and uncommment debugGame();
	// To call methods from a Player-Object directly, you can temporarily comment
	// the "private:" statement in the class definition in Players.hpp.

	int height = 6;
	int width = 7;

	GameBoard fourGame = GameBoard(width, height);

	const bool isMaxPlayer = true;
	HumanPlayer maxPlayerX = HumanPlayer(&fourGame, isMaxPlayer);
	HumanPlayer minPlayerO = HumanPlayer(&fourGame, !isMaxPlayer);

	fourGame.printField();

	bool maxPlayersTurn = true;

	int turn = 0;

	while (fourGame.getUtility() != INT_MAX && fourGame.getUtility() != INT_MIN
			&& !fourGame.isFieldFull())
	{
		turn++;
		cout << "\n";
		cout << " ---------- Turn Number " << turn << " -----------" << endl;
		int move;

		if (maxPlayersTurn)
			move = maxPlayerX.makeMove();
		else
			move = minPlayerO.makeMove();

		if (maxPlayersTurn)
			cout << "MaxPlayer chose column: " << move << "\n";
		else
			cout << "MinPlayer chose column: " << move << "\n";

		fourGame.printField();

		cout << "Utility of current field: " << fourGame.getUtility() << "\n";

		//Just to know...
		//cout << "Min/Max possible utiliy = " << INT_MIN << " / " << INT_MAX << "\n";

		maxPlayersTurn = !maxPlayersTurn;
	}
}

int main(int argc, char* argv[])
{
	//debugGame();
	playGame();
}
