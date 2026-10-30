#include "benchmark_flamegraph.hpp"
#include <iostream>
#include <map>


void benchmark_flamegraph(int depth, int moves)
{

    Board b{};
    b.init("r2q1rk1/2pn1pp1/p1bp3p/1p2p3/4P3/2NP1N2/PPP3PP/R2QR1K1");
    Engine e{};
    e.init(&b);
    
    for (int i = 0; i < moves; i++) {
        b.do_move(e.find_best_move_minimax(depth));
    }

    std::map<std::string, int>::iterator it;
    int counter = 0;
    for (it = b.allmoves_fen_map.begin(); it != b.allmoves_fen_map.end(); it++)
    {
        if(it->second > 1){
            counter++;
        std::cout << it->first    // string (key)
                << ':'
                << it->second   // string's value 
                << std::endl;
    }}
    std::cout<<counter << " " << b.allmoves_fen_map.size();




}