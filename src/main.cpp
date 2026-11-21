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
        const int N = 100000000;
        if(strcmp(argv[1],"testarray_2d") == 0){
            Piece* board[8][8];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row][column] = new Piece(Color::white, Piecetype::pawn, Square(row,column));
                    }
                    else{
                        board[row][column] = new Piece(Color::black, Piecetype::queen, Square(row,column));

                    }
                }
            }    
            int counter = 0;
            for(int i = 0; i < N ; i++){
                for(int row = 0; row < 8; row++){
                    for(int column = 0; column < 8; column++)
                    {
                         if(board[row][column]->type == Piecetype::pawn){
                            counter++;
                         }
                    }
                }
            }
            std::cout << counter << std::endl;
        }
        if(strcmp(argv[1],"testarray_2d_directaccess") == 0){
            Piecetype board[8][8];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row][column] = Piecetype::pawn;
                    }
                    else{
                        board[row][column] = Piecetype::queen;

                    }
                }
            }    
            int counter = 0;
            for(int i = 0; i < N ; i++){
                for(int row = 0; row < 8; row++){
                    for(int column = 0; column < 8; column++)
                    {
                         if(board[row][column] == Piecetype::pawn){
                            counter++;
                         }
                    }
                }
            }
            std::cout << counter << std::endl;
        }
        if(strcmp(argv[1],"testarray_flat") == 0){
            Piece* board[64];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row*8+column] = new Piece(Color::white, Piecetype::pawn, Square(row,column));
                    }
                    else{
                        board[row*8+column] = new Piece(Color::black, Piecetype::queen, Square(row,column));

                    }
                }
            }    
            int counter = 0;
            for(int i = 0; i < N ; i++){
                for(int row = 0; row < 8; row++){
                    for(int column = 0; column < 8; column++)
                    {
                         if(board[row*8+column]->type == Piecetype::pawn){
                            counter++;
                         }
                    }
                }
            }
            std::cout << counter << std::endl;
        }
        
        
        if(strcmp(argv[1],"testarray_flat_directaccess") == 0){
            Piecetype board[64];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row*8+column] = Piecetype::pawn;
                    }
                    else{
                        board[row*8+column] = Piecetype::queen;

                    }
                }
            }   
            int counter = 0;
            for(int i = 0; i < N ; i++){
                for(int row = 0; row < 8; row++){
                    for(int column = 0; column < 8; column++)
                    {
                         if(board[row*8+column] == Piecetype::pawn){
                            counter++;
                         }
                    }
                }
            }
            std::cout << counter << std::endl;
        }
        if(strcmp(argv[1],"testarray_flat_oneloop") == 0){
            Piece* board[64];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row*8+column] = new Piece(Color::white, Piecetype::pawn, Square(row,column));
                    }
                    else{
                        board[row*8+column] = new Piece(Color::black, Piecetype::queen, Square(row,column));

                    }
                }
            }    
            int counter = 0;
            for(int i = 0; i < N ; i++){
                for(int square = 0; square < 64; square++){
                    
                    if(board[square]->type == Piecetype::pawn){
                    counter++;
                    }
                    
                }
            }
            std::cout << counter << std::endl;
        }
        if(strcmp(argv[1],"testarray_flat_oneloop_directaccess") == 0){
            Piecetype board[64];
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(row+column == 3){
                        board[row*8+column] = Piecetype::pawn;
                    }
                    else{
                        board[row*8+column] = Piecetype::queen;

                    }
                }
            }  
            int counter = 0;
            int row = 0;
            int col = 0;

            for(int i = 0; i < N ; i++){
                for(int square = 0; square < 64; square++){
                    
                    if(board[square] == Piecetype::pawn){
                        counter++;
                        row = square%8;
                        col = square/8;
                    }
                    
                }
            }
            std::cout << counter << std::endl;
            std::cout << row << std::endl;
            std::cout << col << std::endl;


        }
    }

    return 0;
}