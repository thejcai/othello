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
     * Initialization
     */
    my_side = side;
    if (my_side == WHITE)
    {
        cerr << "Playing as WHITE\n";
        opponent_side = BLACK;
    }
    else
    {
        cerr << "Playing as BLACK\n";
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
 * Set the board to a given configuration
 */
void Player::setBoard(Board * board)
{
    this->board = board;
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

    // Process opponent move
    board->doMove(opponentsMove, opponent_side);

    // Get moves
    vector<Move*> moves = board->getMoves(my_side);

    // Return nullptr if no moves
    if (moves.size() == 0)
        return nullptr;

    // Move * to_return = getRandomMove(moves);
    // Move * to_return = getHeuristicMove(moves);
    Move * to_return = getTwoPlyMove(moves);

    // cerr << "Making move: " << to_return->getX() << " " << to_return->getY() << endl;

    // Make move on board
    board->doMove(to_return, my_side);

    return to_return;

}

Move * Player::getRandomMove(vector<Move *> moves)
{
    // Seed rand
    srand (time(NULL));

    // Pick and return a random move (used in first AI)
    int r = rand() % moves.size();

    return moves[r];
}

Move * Player::getHeuristicMove(vector<Move *> moves)
{
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
    return to_return;
}

Move * Player::getTwoPlyMove(vector<Move *> moves)
{
    Move * to_return;
    int max_score = INT_MIN;

    // Go through all user possible moves
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        Board * temp_board = board->copy();
        temp_board->doMove(moves[i], my_side);
        
        // Do the same as before, since now we must calculate the heuristic 
        // for each opponent move (for every user move)
        int opp_min_score = INT_MAX;

        // Get opponent's possible moves for this specific move
        vector<Move*> oppmoves = temp_board->getMoves(opponent_side);

        // If opponent cannot make any moves, we calculate heuristic now
        // and return nullptr for opponent move
        if (oppmoves.size() == 0)
        {
            opp_min_score = temp_board->count(my_side) - 
                            temp_board->count(opponent_side);
        }
        else
        {
            // Go through all AI moves and pick lowest score
            for (unsigned int j = 0; j < oppmoves.size(); j++)
            {
                // Make opponent move
                Board * opp_temp_board = temp_board->copy();
                opp_temp_board->doMove(oppmoves[j], opponent_side);

                // Get heuristic for specific move
                int this_score = opp_temp_board->count(my_side) -
                                    opp_temp_board->count(opponent_side);

                if (this_score < opp_min_score)
                {
                    opp_min_score = this_score;
                }
            }
        }

        if (opp_min_score > max_score)
        {
            max_score = opp_min_score;
            to_return = moves[i];
        }

    }

    return to_return;
}