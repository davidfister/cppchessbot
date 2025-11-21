#include "board.hpp"
#include "engine.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  
    std::cout << board.print_board();

    int num_moves = 5;
    int engine_depth = 5; 

    for(int i = 1; i <= num_moves; i++){//do moves
        if(board.is_checkmate()){
            std::cout << "checkmate" << std::endl;
            return 0;
        }
        if(board.is_draw()){
            std::cout << "draw" << std::endl;
            return 0;
        }
        
        if(board.color_to_move == Color::black){
            board.do_move(engine.find_best_move_minimax(engine_depth));
        }
        else{
            board.do_move(engine.find_best_move_minimax(engine_depth));
        }
      

        std::cout << "allMoves() calls:\t " << board.benchmark_num_allMoves_calls<< "\nallMoves cache Calls:\t " << board.benchmark_num_allMoves_cache << "\nundoMove after doMove:\t " << board.benchmark_undoMoveAfterDoMove <<"\ncutoffs: "<< engine.benchmark_cutoffs<< std::endl;
        std::cout<< i << std::endl;

        std::cout<< "---------"<<std::endl;
        std::cout<< board.print_board()<<std::endl;
        std::cout<< "---------"<<std::endl;
        }
}