#ifndef PLAYERS
#define PLAYER

#include<GameBoard.hpp>
using namespace std;

class GenericPlayer
{
    public:
        GenericPlayer(GameBoard* board, bool isMaxPlayer)
                     :board(board), isMaxPlayer(isMaxPlayer) {}
        virtual int makeMove() = 0;
        GameBoard* getBoard(){return board;};
    
    protected:
        GameBoard *board;
        bool isMaxPlayer;

};

class ComputerPlayer: public GenericPlayer
{
    public:
        ComputerPlayer(GameBoard* board, bool isMaxPlayer,
                       bool pruningEnabled, int maxDepth = 5)
                      :GenericPlayer(board, isMaxPlayer),
                       maxDepth(maxDepth), pruningEnabled(pruningEnabled){}
        int makeMove();

    private:
        bool pruningEnabled;
        int maxDepth;
        pair<int, int> getMinimaxValue(int depth, bool isMaxPlayer);
        pair<int, int> getAlphaBetaValue(int depth, bool isMaxPlayer, int alpha, int beta);
};

class HumanPlayer: public GenericPlayer
{
    public:
        HumanPlayer(GameBoard* board, bool isMaxPlayer)
                   :GenericPlayer(board, isMaxPlayer) {}
        int makeMove();
};

#endif
