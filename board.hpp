#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include <vector>
#include <iostream>
#include "common.hpp"
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;
    vector<int> multiplier;

    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    bool isCorner(Move *m);
    bool isNextToCorner(Move *m);

    int getWeightedScore(Side side);

    void setBoard(char data[]);

    vector<Move*> getMoves(Side side);
};

#endif
