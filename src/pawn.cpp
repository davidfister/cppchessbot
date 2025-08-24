#include "pawn.hpp"
#include "colors.hpp"

std::list<Move> Pawn::all_moves()
{
    std::list<Move> all_moves_list{};
    if(color == Color::white){
        all_moves_list.push_back(Move(this->square,Square{this->square.pos_x + 1,this->square.pos_y}));
    }
    else{

    }
    return all_moves_list;
}