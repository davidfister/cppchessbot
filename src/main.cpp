#include "board.hpp"
#include "engine.hpp"
#include "uci.hpp"
#include <string.h>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h>




int main(int argc, char *argv[]){
    
    if(argc == 1){
        uci(4);
    } 
    else {
        if(strcmp(argv[1],"benchmark") == 0){
            Board board = Board();
            board.init("r2qk2r/pp1b1ppp/2n1pn2/2b1N3/2Np4/6P1/PP2PPBP/R1BQ1RK1 w kq - 1 10");
            Engine engine = Engine();
            engine.init(&board);
            Move m = engine.find_best_move_minimax(4);
            std::cout << board.is_square_attacked_cnt <<std::endl;
            std::cout << board.n_do_move+ board.n_undo_move <<std::endl;

            board.do_move(m);
        }
        if(strcmp(argv[1],"time") == 0){
            Board board = Board();
            board.init();
            std::vector<Move>* moves = new std::vector<Move>;;
            auto t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100000; i++){
                board.allMoves(moves);
            }
            auto t2 = std::chrono::high_resolution_clock::now();

            auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            std::cout << ms_int.count() << "ms\n";
        }
        if(strcmp(argv[1],"fen") == 0){
            std::string s;
            std::cout << s <<std::endl;

            std::string line;

            while (getline(std::cin, line)) {
                std::string intermediate;
                std::vector<std::string> tokens;
                std::stringstream line_stream(line);

                while(getline(line_stream, intermediate, ';'))
                {
                    tokens.push_back(intermediate);
                }         

                Board board = Board();
                board.init(tokens[0]);
                std::cout << board.print_board() << std::endl;

                std::cout<< board.get_fen()<<std::endl;

                std::vector<Move>* moves = new std::vector<Move>;
                moves = board.allMoves(moves);
                std::cout << tokens[0] << " me:" << moves->size()<<" real:" << tokens[1] << std::endl;
                std::cout << board.print_board() << std::endl;

                if(std::stoi(tokens[1]) < moves->size()){
                    for (auto m : *moves)
                    {
                        m.print_move();
                    }
                    exit(-1);
                }   
            }
            
        }
        if(strcmp(argv[1],"movegentest") == 0){
            Board board = Board();
            std::vector<Move> * allMovesList = new std::vector<Move>;
            board.init("r2qk2r/pp1b1ppp/2n1pn2/2b1N3/2Np4/6P1/PP2PPBP/R1BQ1RK1 w kq - 1 10");
            for(int i = 0; i < 1000000; i++){
                board.allMoves(allMovesList);
            }            
        }
        if(strcmp(argv[1],"bitboard") == 0){
            Board board = Board();
            board.init();

            std::vector<Move> * allMovesList = new std::vector<Move>;
            Engine engine = Engine();
            engine.init(&board);
            for(int i = 0; i < 10; i++){
                board.allMoves(allMovesList);
                Move m = engine.find_best_move_minimax(3); 
                board.do_move(m);
                std::cout << board.print_board()<<std::endl;
                board.print_bitboard();
            }            
        }
        
    }

    return 0;
}