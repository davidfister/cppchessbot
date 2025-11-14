#include "board.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
    Board* board;
    bool init(Board* board);
    double negamax(int depth, double alpha, double beta);
    double evaluate();
    Move find_best_move();

};

#endif