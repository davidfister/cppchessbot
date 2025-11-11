//Start by generating a slow but working move generator. Initial idea is using array based representation of the board with classes for each piece. 
//After implementing i will probably switch to bitboards or some other board representation. 
#ifndef BOARD_HPP
#define BOARD_HPP


#include"piece.hpp"
#include <string>

class Board
{
    Piece* board[8][8]; //[row]][column]
    Color color_to_move = Color::white;
    bool is_valid_dest_square(int row, int column, Color color_of_moving_piece);
    bool is_valid_dest_square_pawn(int row, int column, Color color);
    bool is_valid_dest_square_king(int row, int column, Color color);

public:
    void init();
    std::list<Move> allMoves();
    std::string print_board();
    bool do_move(Move move);
};

#endif