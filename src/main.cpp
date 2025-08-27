#include"board.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    std::cout << board.print_board();
    std::string all_moves = "";
    for (Move m : board.allMoves()){
        all_moves += 'a' + m.start_square.column;
        all_moves += '1' + m.start_square.row;
        all_moves += " to ";
        all_moves += 'a' + m.end_square.column;
        all_moves += '1' + m.end_square.row;
        all_moves += "\n";
    }
    std::cout << all_moves;
            
            
    int num_pops = 5;

    while(board.allMoves().size() > 0){
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