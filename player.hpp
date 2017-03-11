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
    Move *getMinimax(std::vector<Move *> moves, int depth);
    Move *getMaxMove(Board * b, std::vector<Move *> moves, 
        int depth, Side s);
    Move *getMinMove(Board * b, std::vector<Move *> moves, 
        int depth, Side s);
    void setBoard(Board * board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Side my_side;
    Side opponent_side;
    Board * board;
};

#endif
