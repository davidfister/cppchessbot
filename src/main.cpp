#include "board.hpp"
#include "engine.hpp"
#include <iostream>
#include <chrono>

int main(){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  

    int num_moves = 15;
    int engine_depth = 2; 


    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= num_moves; i++){//do moves
        if(board.is_checkmate()){
            std::cout << "checkmate" << std::endl;
            return 0;
        }
        if(board.is_draw()){
            std::cout << "draw" << std::endl;
            return 0;
        }
        
        if(board.color_to_move == Color::white){
            board.do_move(engine.find_best_move_minimax(engine_depth));
        }
        else{
            board.do_move(engine.find_best_move_minimax(1));
        }
      

        //std::cout << "\nallMoves() calls:\t " << board.benchmark_num_allMoves_calls  <<"\ncutoffs: "<< engine.benchmark_cutoffs<< std::endl;
        //std::cout<< i << " " << !board.color_to_move << std::endl;

        // std::cout<< "---------"<<std::endl;
        // std::cout<< board.print_board()<<std::endl;
        // std::cout<< "--------- "<<std::endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    std::cout << ms_int.count() << std::endl;
    std::cout << board.benchmark_ms.count() << std::endl;
    std::cout << (double) ms_int.count()/board.benchmark_ms.count() << std::endl;
}