#include "board.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine
{
public:
    Board* board;
    bool init(Board* board);
    double negamax(int depth, double alpha, double beta);
    double minimax_max(int depth,double alpha, double beta);
    double minimax_min(int depth,double alpha, double beta);

    double evaluate();
    double evaluate_minimax(int depth);

    Move find_best_move_negamax(int depth);
    Move find_best_move_minimax(int depth);


    //benchmark
    int benchmark_cutoffs = 0;
    int benchmark_nodes = 0;
};

#endif