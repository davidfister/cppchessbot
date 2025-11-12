#include "move.hpp"
#include <iostream>

Move::Move(Square start_square, Square end_square, Color color_moved_piece, Piecetype moved_piece, Piecetype captured_piece)
{
    this->start_square = start_square;
    this->end_square = end_square;
    this->color_moved_piece = color_moved_piece;
    this->moved_piece = moved_piece;
    this->captured_piece = captured_piece;
}

void Move::print_move() {
    std::string move_str{};
    move_str += 'a' + this->start_square.column;
    move_str += '1' + this->start_square.row;
    move_str += " to ";
    move_str += 'a' + this->end_square.column;
    move_str += '1' + this->end_square.row;
    move_str += "\n";
    std::cout<<move_str;
};