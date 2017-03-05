#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    my_side = side;
    if (my_side == WHITE)
        opponent_side = BLACK;
    else
        opponent_side = WHITE;

    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {

}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    
    // Process opponent move
    board->doMove(opponentsMove, opponent_side);

    cerr << "Make opponent move\n" << endl;

    // Get moves
    vector<Move*> moves = board->getMoves(my_side);

    cerr << "Got moves\n";

    // Return nullptr if no moves
    if (moves.size() == 0)
        return nullptr;

    cerr << "Checked if neg\n";

    // Pick and return a random move
    int r = rand() % moves.size();

    cerr << "Got random move, returning now\n";

    return moves[r];

}
