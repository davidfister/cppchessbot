//Start by generating a slow but working move generator. Initial idea is using array based representation of the board with classes for each piece. 
//After implementing i will probably switch to bitboards or some other board representation. 
#ifndef BOARD_HPP
#define BOARD_HPP


#include"piece.hpp"
#include <string>

class Board
{
    Piece* board[8][8]; //[1][0] = b1
    Color color_to_move = Color::white;
    bool is_valid_dest_square(int row, int column, Color color);
public:
    void init();
    std::list<Move> allMoves();
    std::string print_board();
};

#endif