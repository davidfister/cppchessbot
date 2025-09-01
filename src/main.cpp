#include"board.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    std::cout << board.print_board();
    
            
            
    int num_pops = 7;
    for(int i = 0; i < 3 && board.allMoves().size() > 0;i++){//do moves
        std::list<Move> mvs = board.allMoves();
        if(num_pops < mvs.size()-1){
            num_pops++;
        }
        else{
            num_pops = 0;
        }

        for(int i = 0; i < num_pops; i++){
            mvs.pop_front();
        }

        board.do_move(mvs.front());
        std::cout<<board.print_board()<<std::endl;
    }
}