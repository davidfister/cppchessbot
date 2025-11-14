#include"board.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    std::cout << board.print_board();
    

    int num_moves = 59; 

    for(int i = 1; i <= num_moves && board.allMoves().size() > 0;i++){//do moves
        std::list<Move> mvs = board.allMoves();
        while (mvs.size() > 1)
        {
            if(mvs.front().captured_piece == Piecetype::none){
                mvs.pop_front();
            }
            else{
                mvs.pop_back();

            }
        }
        
        board.do_move(mvs.front());
        std::cout<< i << std::endl;
        std::cout<<board.print_board()<<std::endl;
        std::cout<<"---------"<<std::endl;
        }
}