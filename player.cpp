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
    {
        cerr << "Color: white\n";
        opponent_side = BLACK;
    }
    else
    {
        cerr << "Color: black\n";
        opponent_side = WHITE;
    }

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

    // Get moves
    vector<Move*> moves = board->getMoves(my_side);

    // Return nullptr if no moves
    if (moves.size() == 0)
        return nullptr;

    // Pick and return a random move (used in first AI)
    // int r = rand() % moves.size();

    // Look through moves and calculate scores
    Move * to_return;
    int max_score = INT_MIN;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        Board * temp_board = board->copy();
        temp_board->doMove(moves[i], my_side);
        int this_score = temp_board->count(my_side) - 
                            temp_board->count(opponent_side);

        // Increase corner value
        if (temp_board->isCorner(moves[i]))
        {
            this_score = INT_MAX;
        }

        // Decrease value for spaces right next to corner
        if (temp_board->isNextToCorner(moves[i]))
        {
            if (this_score < 0)
                this_score *= 3;
            else
                this_score *= -3;
        }

        if (this_score > max_score)
        {
            max_score = this_score;
            to_return = moves[i];
        }
    }

    cerr << "Making move: " << to_return->getX() << " " << to_return->getY() << endl;

    // Make move on board
    board->doMove(to_return, my_side);

    return to_return;

}
