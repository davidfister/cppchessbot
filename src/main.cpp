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
            board.init();
            Engine engine = Engine();
            engine.init(&board);
            Move m = engine.find_best_move_minimax(5);
            board.do_move(m);
        }
        if(strcmp(argv[1],"time") == 0){
            Board board = Board();
            board.init();
            std::vector<Move>* moves = NULL;
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

                std::vector<Move>* moves = NULL;
                moves = board.allMoves(moves);
                std::cout << tokens[0] << " me:" << moves->size()<<" real:" << tokens[1] << std::endl;
                std::cout << board.print_board() << std::endl;

                if(std::stoi(tokens[1]) != moves->size()){
                    for (auto m : *moves)
                    {
                        m.print_move();
                    }
                    exit(-1);
                }   
            }
            
        }
    }

    return 0;
}