#include "board.hpp"
#include "engine.hpp"
#include <iostream>
#include <chrono>

int debug(int num_moves, int engine_depth){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  


    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i = 1; i <= num_moves; i++){//do moves
        std::cout << engine.evaluate_minimax(0) <<std::endl;
        std::cout<< board.print_board()<<std::endl;
        if(board.is_checkmate()){
            std::cout << "checkmate" << std::endl;
            return 0;
        }
        if(board.is_draw()){
            std::cout << "draw" << std::endl;
            return 0;
        }

        /*std::list<Move>* moves = new std::list<Move>;

        for(auto m : *moves){
            m.print_move();
        }*/
       /*
        if(board.color_to_move == Color::black){
            board.do_move(engine.find_best_move_minimax(engine_depth));
        }
        else{
            board.do_move(engine.find_best_move_minimax(engine_depth));

            
        }*/
        std::string s;
        std::cin >> s;
        board.do_uci_move(s);
                std::cout<< board.color_to_move << !board.color_to_move <<std::endl;

        board.do_move(engine.find_best_move_minimax(1));

        std::cout<< board.color_to_move << !board.color_to_move <<std::endl;



        //std::cout << "\nallMoves() calls:\t " << board.benchmark_num_allMoves_calls  <<"\ncutoffs: "<< engine.benchmark_cutoffs<< std::endl;
        //std::cout<< i << " " << !board.color_to_move << std::endl;

        // std::cout<< "---------"<<std::endl;
        
        // std::cout<< "--------- "<<std::endl;
        

    }
    std::cout << engine.benchmark_cutoffs << " " << engine.benchmark_nodes << " " << (double) engine.benchmark_cutoffs/engine.benchmark_nodes << std::endl;
    
    
    std::cout << "benchmark_calls_allMoves " << board.benchmark_calls_allMoves << std::endl;
    std::cout << "benchmark_calls_do_move " << board.benchmark_calls_do_move << std::endl;
    std::cout << "benchmark_calls_do_nullmove " << board.benchmark_calls_do_nullmove << std::endl;
    std::cout << "benchmark_calls_undo_move " << board.benchmark_calls_undo_move << std::endl;
    std::cout << "benchmark_calls_undo_nullmove " << board.benchmark_calls_undo_nullmove << std::endl;
    std::cout << "benchmark_calls_is_checkmate " << board.benchmark_calls_is_checkmate << std::endl;
    std::cout << "benchmark_calls_is_draw " << board.benchmark_calls_is_draw << std::endl;
    std::cout << "benchmark_calls_valid_coordinates " << board.benchmark_calls_valid_coordinates << std::endl;
    std::cout << "benchmark_calls_is_valid_dest_square " << board.benchmark_calls_is_valid_dest_square << std::endl;
    std::cout << "benchmark_calls_valid_is_legal_move " << board.benchmark_calls_valid_is_legal_move << std::endl;
    std::cout << "benchmark_calls_valid_is_legal_nullmove " << board.benchmark_calls_valid_is_legal_nullmove << std::endl;
    
    long sum = board.benchmark_calls_allMoves + board.benchmark_calls_do_move + board.benchmark_calls_do_nullmove + board.benchmark_calls_undo_move + board.benchmark_calls_undo_nullmove + board.benchmark_calls_is_checkmate + board.benchmark_calls_is_draw + board.benchmark_calls_valid_coordinates + board.benchmark_calls_is_valid_dest_square + board.benchmark_calls_valid_is_legal_move + board.benchmark_calls_valid_is_legal_nullmove;
    
    std::cout << "sum calls " << sum << std::endl;// auto t2 = std::chrono::high_resolution_clock::now();
    // auto ms_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    // std::cout << ms_int.count() << std::endl;
    // std::cout << board.benchmark_ms.count() << std::endl;
    // std::cout << (double) board.benchmark_ms.count()/ms_int.count() << std::endl;
    return 0;
}
