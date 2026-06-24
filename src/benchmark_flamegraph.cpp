#include "benchmark_flamegraph.hpp"
#include <iostream>


void benchmark_flamegraph(int depth, int moves)
{

    Board b{};
    b.init();
    Engine e{};
    e.init(&b);
    
    for (int i = 0; i < moves; i++) {
        b.do_move(e.find_best_move_minimax(depth));
    }


}