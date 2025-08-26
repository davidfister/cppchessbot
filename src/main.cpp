#include"board.hpp"
#include <iostream>

int main(){
    Board board = Board();
    board.init();
    std::cout << board.print_board();
}