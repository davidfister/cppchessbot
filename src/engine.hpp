#include "board.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
    Board* board;
    bool init(Board* board);
    double negamax(int depth, double alpha, double beta);
    double minimax_max(int depth);
    double minimax_min(int depth);

    double evaluate();
    double evaluate_minimax();

    Move find_best_move_negamax(int depth);
    Move find_best_move_minimax(int depth);


    //benchmark
    int benchmark_cutoffs = 0;
};

#endif