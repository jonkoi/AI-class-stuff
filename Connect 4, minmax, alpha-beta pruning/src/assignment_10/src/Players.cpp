#include<Players.hpp>
#include<climits>
#include<algorithm> //includes std::max
#include<string>
#include<iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

using namespace std;

static int node_count = 0;

int ComputerPlayer::makeMove()
{
	pair<int, int> column;

	clock_t start = clock();

	node_count = 0;

	if (this->pruningEnabled)
	{
		column = getAlphaBetaValue(this->maxDepth, this->isMaxPlayer, INT_MIN, INT_MAX);
	}
	else
	{
		column = getMinimaxValue(this->maxDepth, this->isMaxPlayer);
	}

	if (column.second >= 0 && this->board->isValidMove(column.second))
	{
		this->board->executeMove(column.second, this->isMaxPlayer);
	}

	cout << "Nodes searched: " << node_count << endl;
	cout << "Time taken: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;

	return column.second;
}

pair<int, int> minimize(GameBoard* board, int depth, bool isMaxPlayer);

pair<int, int> maximize(GameBoard* board, int depth, bool isMaxPlayer)
{
	node_count++;
	// Call score of our board
	int score = board->getUtility();

	// Break
	if (board->isFieldFull() || depth == 0 || score == INT_MIN || score == INT_MAX)
		return make_pair(score, -1);

	// Column, Score
	pair<int, int> max = make_pair(INT_MIN, -1);

	// For all possible moves
	for (int column = 0; column < board->getWidth(); column++)
	{
		if (board->isValidMove(column))
		{
			board->executeMove(column, isMaxPlayer);

			pair<int, int> next_move = minimize(board, depth - 1, !isMaxPlayer);

			board->undoMove(column);

			// Evaluate new move
			if (max.second == -1 || next_move.first > max.first)
			{
				max.second = column;
				max.first = next_move.first;
			}
		}
	}

	return max;
}

pair<int, int> minimize(GameBoard* board, int depth, bool isMaxPlayer)
{
	node_count++;
	// Call score of our board
	int score = board->getUtility();

	// Break
	if (board->isFieldFull() || depth == 0 || score == INT_MIN || score == INT_MAX)
		return make_pair(score, -1);

	// Column, Score
	pair<int, int> min = make_pair(INT_MAX, -1);

	// For all possible moves
	for (int column = 0; column < board->getWidth(); column++)
	{
		if (board->isValidMove(column))
		{
			board->executeMove(column, isMaxPlayer);

			pair<int, int> next_move = maximize(board, depth - 1, !isMaxPlayer);

			board->undoMove(column);

			// Evaluate new move
			if (min.second == -1 || next_move.first < min.first)
			{
				min.second = column;
				min.first = next_move.first;
			}
		}
	}

	return min;
}

pair<int, int> ComputerPlayer::getMinimaxValue(int depth, bool isMaxPlayer)
{
	return maximize(this->getBoard(), depth, isMaxPlayer);
}

pair<int, int> minimizeBeta(GameBoard* board, int depth, bool isMaxPlayer, int alpha, int beta);

pair<int, int> maximizeAlpha(GameBoard* board, int depth, bool isMaxPlayer, int alpha, int beta)
{
	node_count++;
	// Call score of our board
	int score = board->getUtility();

	// Break
	if (board->isFieldFull() || depth == 0 || score == INT_MIN || score == INT_MAX)
		return make_pair(score, -1);

	// Column, Score
	pair<int, int> max = make_pair(INT_MIN, -1);

	// For all possible moves
	for (int column = 0; column < board->getWidth(); column++)
	{

		if (board->isValidMove(column))
		{
			board->executeMove(column, isMaxPlayer);

			pair<int, int> next_move = minimizeBeta(board, depth - 1, !isMaxPlayer, alpha, beta);

			board->undoMove(column);

			// Evaluate new move
			if (max.second == -1 || next_move.first > max.first)
			{
				max.second = column;
				max.first = next_move.first;
				alpha = next_move.first;
			}
			if(alpha >= beta)
			{
				return max;
			}
		}
	}

	return max;
}

pair<int, int> minimizeBeta(GameBoard* board, int depth, bool isMaxPlayer, int alpha, int beta)
{
	node_count++;
	// Call score of our board
	int score = board->getUtility();

	// Break
	if (board->isFieldFull() || depth == 0 || score == INT_MIN || score == INT_MAX)
		return make_pair(score, -1);

	// Column, Score
	pair<int, int> min = make_pair(INT_MAX, -1);

	// For all possible moves
	for (int column = 0; column < board->getWidth(); column++)
	{
		if (board->isValidMove(column))
		{
			board->executeMove(column, isMaxPlayer);

			pair<int, int> next_move = maximizeAlpha(board, depth - 1, !isMaxPlayer, alpha, beta);

			board->undoMove(column);

			// Evaluate new move
			if (min.second == -1 || next_move.first < min.first)
			{
				min.second = column;
				min.first = next_move.first;
				beta = next_move.first;
			}

			if(alpha >= beta)
			{
				return min;
			}
		}
	}

	return min;
}

pair<int, int> ComputerPlayer::getAlphaBetaValue(int depth, bool isMaxPlayer,
		int alpha, int beta)
{
	return maximizeAlpha(this->getBoard(), depth, isMaxPlayer, alpha, beta);
}

int HumanPlayer::makeMove()
{
	string inputString;

	cout << "Choose column: ";
	cin >> inputString;
	int column = (int) inputString[0] - 48;

	this->board->executeMove(column - 1, this->isMaxPlayer);

	return column;
}
