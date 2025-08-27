#include"board.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    std::cout << board.print_board();
    std::string all_moves = "";
    for (Move m : board.allMoves()){
        all_moves += 'a' + m.start_square.pos_y;
        all_moves += '1' + m.start_square.pos_x;
        all_moves += " to ";
        all_moves += 'a' + m.end_square.pos_y;
        all_moves += '1' + m.end_square.pos_x;
        all_moves += "\n";
    }

    std::cout << all_moves;

}