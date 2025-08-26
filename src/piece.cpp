#include "piece.hpp"
#include "piecetypes.hpp"

Piece::Piece(Color color, Piecetype type)
{
    this->color = color;
    this->type = type;
}