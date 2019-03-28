#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include<vector>
// temporary, delete later!
#include<iostream>
using namespace std;

class GameBoard
{
    public:
        GameBoard(int width, int heigth);
        void printField();
        void executeMove(int column, bool maxPlayersTurn);
        void undoMove(int column); //needed for undoing moves after evaluating their utility
        bool isValidMove(int column);
        bool nextMoveWins(bool maxPlayersTurn);
        bool isFieldFull();
        int getUtility();

        int getWidth() {return width;}
        int getHeight() {return height;}
        vector<vector<char>> getFields() {return fields;}

    public:
        const char minPlayerSymbol = 'O';
        const char maxPlayerSymbol = 'X';
        const char noTokenSymbol = '.';
        int width; //number of columns
        int height; //number of rows

        vector<vector<char>> fields;
        //first index denotes columns,
        //second index denotes field in column from bottom to top.

        vector<vector<int>> getAllQuadruplesInField();
        //returns a list of all possible quadruples, that can be extracted from
        //the fields in the game board. These can be used to calculate the
        //utility of a given board.
};

#endif
