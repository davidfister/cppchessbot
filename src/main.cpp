#include "board.hpp"
#include "engine.hpp"
#include "uci.hpp"
#include <string.h>
#include <iostream>


int main(int argc, char *argv[]){
    
    if(argc == 1){
        uci(4);
    } 
    else {
        if(strcmp(argv[1],"benchmark") == 0){
            Board board = Board();
            board.init();
            Engine engine = Engine();
            engine.init(&board);
            Move m = engine.find_best_move_minimax(5);
            board.do_move(m);
        }
    }

    return 0;
}