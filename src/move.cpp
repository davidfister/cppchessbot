#include "move.hpp"
#include <iostream>

Move::Move(std::string s, Color color_moved_piece)
{
    Square start_square = Square(-((int)'1' - s.at(1)),-((int)'a' - s.at(0)));
    Square end_square = Square(-((int)'1' - s.at(3)),-((int)'a' - s.at(2)));
    this->start_square = start_square;
    this->end_square = end_square;
    this->color_moved_piece = color_moved_piece;
    this->moved_piece = Piecetype::none;
    this->captured_piece = Piecetype::none;

    if(captured_piece != Piecetype::none){
        this->is_capture = true;
    }
    else{
        this->is_capture = false;
    }
}

Move::Move(Square start_square, Square end_square, Color color_moved_piece, Piecetype moved_piece, Piecetype captured_piece)
{
    this->start_square = start_square;
    this->end_square = end_square;
    this->color_moved_piece = color_moved_piece;
    this->moved_piece = moved_piece;
    this->captured_piece = captured_piece;

    if(captured_piece != Piecetype::none){
        this->is_capture = true;
    }
    else{
        this->is_capture = false;
    }
}

void Move::print_move() {
    std::cout<<to_string()<<std::endl;
}
std::string Move::to_string()
{
    std::string move_str{};
    move_str += 'a' + this->start_square.column;
    move_str += '1' + this->start_square.row;
    move_str += 'a' + this->end_square.column;
    move_str += '1' + this->end_square.row;
    return move_str;
};