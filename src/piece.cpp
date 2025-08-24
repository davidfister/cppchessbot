#include "piece.hpp"

Piece::Piece()
{
}

// unnecessary atp
bool Piece::set_pos(uint8_t x, uint8_t y)
{
    Square s{x,y};
    return true;
}

bool Piece::set_type(char type)
{
    this->type = type;
    return true;
}

bool Piece::set_color(Color color)
{
    this->color = color;
    return false;
}

std::list<Move> Piece::all_moves()
{
        return std::list<Move>{};
}