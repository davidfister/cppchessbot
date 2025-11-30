#include "move.hpp"
#include <iostream>

Move::Move(Square start_square, Square end_square, Color color_moved_piece, Piecetype moved_piece, Piecetype captured_piece)
{
    this->start_square = start_square;
    this->end_square = end_square;
    this->color_moved_piece = color_moved_piece;
    this->moved_piece = moved_piece;
    this->captured_piece = captured_piece;
    this->is_promotion = false;
    this->is_en_passant = false;
    this->is_castle = false;


    if(moved_piece == Piecetype::pawn){
        if(color_moved_piece == Color::white){
            if(end_square.column != start_square.column){
                if(captured_piece == Piecetype::none){
                    this->is_en_passant = true;
                    captured_piece = Piecetype::pawn;
                }
            }
            else if(end_square.row == 7){
                this->is_promotion = true;
            }
        }
        else if(color_moved_piece == Color::black){
            if(end_square.column != start_square.column){
                if(captured_piece == Piecetype::none){
                    this->is_en_passant = true;
                    captured_piece = Piecetype::pawn;

                }
            }
            else if(end_square.row == 0){
                this->is_promotion = true;
            }
        }
    }

    if(captured_piece != Piecetype::none){
        this->is_capture = true;
    }
    else{
        this->is_capture = false;
    }
    if(moved_piece == Piecetype::king){
        if(abs(end_square.column - end_square.column) > 1){
            is_en_passant = true;
        }
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
    if(this->is_promotion){
        move_str += 'q';
    }
    return move_str;
};