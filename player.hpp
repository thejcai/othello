#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <cstdlib>
#include <climits>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *getRandomMove(vector<Move*> moves);
    Move *getHeuristicMove(vector<Move*> moves);
    Move *getTwoPlyMove(vector<Move *> moves);
    int getOppMoveValue(Board * board, Move * move);

    // Minimax methods
    Move *getMinimax(Board * b, std::vector<Move *> m);
    int getMaxMove(Board * b, int depth, int alpha, int beta);
    int getMinMove(Board * b, int depth, int alpha, int beta);
    int getScore(Board * b);

    void setBoard(Board * board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Side my_side;
    Side opponent_side;
    Board * board;
};

#endif
