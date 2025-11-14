#include "board.hpp"
#include "engie.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  
    std::cout << board.print_board();
    

    int num_moves = 50; 

    for(int i = 1; i <= num_moves; i++){//do moves
        if(board.allMoves().size() == 0){
            if(board.is_checkmate()){
                std::cout << "checkmate" << std::endl;
                return 0;
            }
            if(board.is_draw()){
                std::cout << "draw" << std::endl;
                return 0;
            }
        }
        if(i % 2 == 1){
            board.do_move(engine.find_best_move());
        }
        else{
            board.do_move(board.allMoves().front());
        }

        
        std::cout<< i << std::endl;
        std::cout<<board.print_board()<<std::endl;
        std::cout<<"---------"<<std::endl;
        }
}