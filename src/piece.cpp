#include "piece.hpp"

//unnecessary atp
bool Piece::set_pos(uint8_t x, uint8_t y)
{
    this->pos = (x<<4) | y;
    return true;
}

bool Piece::set_type(char type)
{
    this->type = type;
    return true;
}
