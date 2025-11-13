#include "piece.hpp"
#include "piecetypes.hpp"

Piece::Piece(Color color, Piecetype type, Square square)
{
    this->color = color;
    this->type = type;
    this->square = square;
}