#include"GameBoard.hpp"
#include<iostream>
#include<vector>
#include<climits> // includes INT_MIN and INT_MAX
#include<algorithm> // includes std::count
#include<cmath>

using namespace std;

GameBoard::GameBoard(const int width, const int height) :
		width(width), height(height)
{
	fields = vector<vector<char>>(width, vector<char>(height, noTokenSymbol));
}

void GameBoard::printField()
{
	cout << " ";

	for (int i = 1; i <= this->width; i++)
	{
		cout << i << " ";
	}

	cout << endl;

	for (int i = this->height - 1; i >= 0; i--)
	{
		cout << "|";

		for (int j = 0; j < this->width; j++)
		{
			if (j == this->width - 1)
			{
				cout << this->fields[j][i];
			}
			else
			{
				cout << this->fields[j][i] << " ";
			}
		}

		cout << "|" << endl;
	}

	cout << "-";

	for (int i = 0; i < this->width; ++i)
	{
		cout << "--";
	}
	cout << endl;
}

void GameBoard::executeMove(int column, bool maxPlayersTurn)
{
	if (column >= 0 && column <= this->width && isValidMove(column))
	{
		for (int i = 0; i < this->height; i++)
		{
			if (this->fields[column][i] == '.')
			{
				if (maxPlayersTurn)
				{
					this->fields[column][i] = 'X';
				}
				else
				{
					this->fields[column][i] = 'O';
				}

				return;
			}
		}
	}
	else
	{
		cout << "Move in column " << column << " not possible" << endl;
	}
}

void GameBoard::undoMove(int column)
{
	for (int i = this->height - 1; i >= 0; i--)
	{
		if (this->fields[column][i] == 'X' || this->fields[column][i] == 'O')
		{
			this->fields[column][i] = '.';

			return;
		}
	}

}

bool GameBoard::isValidMove(int column)
{
	if (this->fields[column][this->height - 1] == '.')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameBoard::isFieldFull()
{
	for (int i = 0; i < this->width; i++)
	{
		if (this->fields[i][this->height - 1] == '.')
		{
			return false;
		}
	}

	return true;
}

vector<vector<int>> GameBoard::getAllQuadruplesInField()
{
	vector<vector<int>> evaluationTable(this->width, vector<int>(this->height));

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			int countQuadruples = 0;

			int l = 3;

			for (int k = 0; k < 4; k++)
			{
				if ((j + l) < this->width && (j - k) >= 0)
				{
					countQuadruples++;
				}

				if ((i + l) < this->height && (i - k) >= 0)
				{
					countQuadruples++;
				}

				if ((j + l) < this->width && (i + l) < this->height
						&& (i - k) >= 0 && (j - k) >= 0)
				{
					countQuadruples++;
				}

				if ((j - l) >= 0 && (i + l) < this->height && (i - k) >= 0
						&& (j + k) < this->width)
				{
					countQuadruples++;
				}
				l--;
			}

			evaluationTable[j][i] = countQuadruples;
		}
	}

	return evaluationTable;
}

bool GameBoard::nextMoveWins(bool maxPlayersTurn)
{
	char symbol = '.';

	if (maxPlayersTurn)
	{
		symbol = this->maxPlayerSymbol;
	}
	else
	{
		symbol = this->minPlayerSymbol;
	}

	// check horizontal win in next round
	for (int row = 0; row < this->height; row++)
	{
		for (int column = 0; column < this->width - 3; column++)
		{
			if (this->fields[column][row] == symbol
					&& symbol == this->fields[column + 1][row]
					&& symbol == this->fields[column + 2][row]
					&& '.' == this->fields[column + 3][row])
			{
				if (row > 0 && this->fields[column + 3][row - 1] != '.')
				{
					return true;
				}
				else
				{
					return true;
				}
			}
		}
	}

	// check vertical win in next round
	for (int row = 0; row < this->height - 3; row++)
	{
		for (int column = 0; column < this->width; column++)
		{
			if (this->fields[column][row] == symbol
					&& symbol == this->fields[column][row + 1]
					&& symbol == this->fields[column][row + 2]
					&& '.' == this->fields[column][row + 3])
			{
				return true;
			}
		}
	}

	// check for a diagonal win (positive slope) in next round
	for (int row = 0; row < this->height - 3; row++)
	{
		for (int column = 0; column < this->width - 3; column++)
		{
			if (this->fields[column][row] == symbol
					&& symbol == this->fields[column + 1][row + 1]
					&& symbol == this->fields[column + 2][row + 2]
					&& '.' == this->fields[column + 3][row + 3])
			{
				if (this->fields[column + 3][row + 2] != '.')
				{
					return true;
				}
			}
		}
	}
	// check for a diagonal win (negative slope)
	for (int row = 3; row < this->height; row++)
	{
		for (int column = 0; column < this->width - 3; column++)
		{
			if (this->fields[column][row] == symbol
					&& symbol == this->fields[column + 1][row - 1]
					&& symbol == this->fields[column + 2][row - 2]
					&& '.' == this->fields[column + 3][row - 3])
			{
				if ((row - 3) > 0 && this->fields[column + 3][row - 4] != '.')
				{
					return true;
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}

/*int GameBoard::getUtility()
 {
 // check horizontal win
 for (int row = 0; row < this->height; row++)
 {
 for (int column = 0; column < this->width - 3; column++)
 {
 if (this->fields[column][row] != '.'
 && this->fields[column][row]
 == this->fields[column + 1][row]
 && this->fields[column][row]
 == this->fields[column + 2][row]
 && this->fields[column][row]
 == this->fields[column + 3][row])
 {
 if (this->fields[column][row] == this->maxPlayerSymbol)
 {
 return INT_MAX;
 }
 else
 {
 return INT_MIN;
 }
 }
 }
 }

 // check for a vertical win
 for (int row = 0; row < this->height - 3; row++)
 {
 for (int column = 0; column < this->width; column++)
 {
 if (this->fields[column][row] != '.'
 && this->fields[column][row]
 == this->fields[column][row + 1]
 && this->fields[column][row]
 == this->fields[column][row + 2]
 && this->fields[column][row]
 == this->fields[column][row + 3])
 {
 if (this->fields[column][row] == this->maxPlayerSymbol)
 {
 return INT_MAX;
 }
 else
 {
 return INT_MIN;
 }
 }
 }
 }
 // check for a diagonal win (positive slope)
 for (int row = 0; row < this->height - 3; row++)
 {
 for (int column = 0; column < this->width - 3; column++)
 {
 if (this->fields[column][row] != '.'
 && this->fields[column][row]
 == this->fields[column + 1][row + 1]
 && this->fields[column][row]
 == this->fields[column + 2][row + 2]
 && this->fields[column][row]
 == this->fields[column + 3][row + 3])
 {
 if (this->fields[column][row] == this->maxPlayerSymbol)
 {
 return INT_MAX;
 }
 else
 {
 return INT_MIN;
 }
 }
 }
 }
 // check for a diagonal win (negative slope)
 for (int row = 3; row < this->height; row++)
 {
 for (int column = 0; column < this->width - 3; column++)
 {
 if (this->fields[column][row] != '.'
 && this->fields[column][row]
 == this->fields[column + 1][row - 1]
 && this->fields[column][row]
 == this->fields[column + 2][row - 2]
 && this->fields[column][row]
 == this->fields[column + 3][row - 3])
 {
 if (this->fields[column][row] == this->maxPlayerSymbol)
 {
 return INT_MAX;
 }
 else
 {
 return INT_MIN;
 }
 }
 }
 }

 vector<vector<int> > evaluationTable = getAllQuadruplesInField();

 int utility = 0;

 for (auto const &n1 : evaluationTable)
 {
 for (auto const &n2 : n1)
 {
 utility += n2;
 }
 }

 utility = (int) (utility / 2);

 int sum = 0;
 for (int i = 0; i < this->height; i++)
 {
 for (int j = 0; j < this->width; j++)
 {
 if (this->fields[j][i] == this->maxPlayerSymbol)
 {
 sum += evaluationTable[j][i];
 }
 else if (this->fields[j][i] == this->minPlayerSymbol)
 {
 sum -= evaluationTable[j][i];
 }
 }
 }

 if (nextMoveWins(true))
 {
 sum += 1000;
 }

 if (nextMoveWins(false))
 {
 sum -= 1000;
 }

 return utility + sum;
 }*/

int scorePosition(vector<vector<char>> fields, int row, int column, int delta_y,
		int delta_x)
{
	int human = 0;
	int computer = 0;

	// Determine score through amount of available chips
	for (int i = 0; i < 4; i++)
	{
		if (fields[column][row] == 'X')
		{
			computer++; // Add for each human chip
		}
		else if (fields[column][row] == 'O')
		{
			human++; // Add for each computer chip
		}

		// Moving through our board
		row += delta_y;
		column += delta_x;
	}

	// Marking winning/returning score
	if (human == 4)
	{
		return INT_MIN;
	}
	else if (computer == 4)
	{
		return INT_MAX;
	}
	else
	{
		return computer;
	}
}

/**
 * Returns the overall score for our board.
 *
 * @return {number}
 */
int GameBoard::getUtility()
{
	int points = 0;

	int vertical_points = 0;
	int horizontal_points = 0;
	int diagonal_points1 = 0;
	int diagonal_points2 = 0;

	for (int row = 0; row < this->getHeight() - 3; row++)
	{
		for (int column = 0; column < this->getWidth(); column++)
		{
			int score = scorePosition(this->getFields(), row, column, 1, 0);
			if (score == INT_MAX)
				return INT_MAX;
			if (score == INT_MIN)
				return INT_MIN;
			vertical_points += score;
		}
	}

	for (int row = 0; row < this->getHeight(); row++)
	{
		for (int column = 0; column < this->getWidth() - 3; column++)
		{
			int score = scorePosition(this->getFields(), row, column, 0, 1);
			if (score == INT_MAX)
				return INT_MAX;
			if (score == INT_MIN)
				return INT_MIN;
			horizontal_points += score;
		}
	}

	for (int row = 0; row < this->getHeight() - 3; row++)
	{
		for (int column = 0; column < this->getWidth() - 3; column++)
		{
			int score = scorePosition(this->getFields(), row, column, 1, 1);
			if (score == INT_MAX)
				return INT_MAX;
			if (score == INT_MIN)
				return INT_MIN;
			diagonal_points1 += score;
		}
	}

	for (int row = 3; row < this->getHeight(); row++)
	{
		for (int column = 0; column <= this->getWidth() - 4; column++)
		{
			int score = scorePosition(this->getFields(), row, column, -1, +1);
			if(score == INT_MAX)
			return INT_MAX;
			if (score == INT_MIN)
				return INT_MIN;
			diagonal_points2 += score;
		}

	}

	points = horizontal_points + vertical_points + diagonal_points1
			+ diagonal_points2;
	return points;
}
