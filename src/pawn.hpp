#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece
{
    std::list<Move> all_moves();
};

#endif