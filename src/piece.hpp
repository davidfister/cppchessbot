#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <list>
#include "move.hpp"
#include "colors.hpp"
#include "piecetypes.hpp"

class Piece{
public:
    Piece(Color color, Piecetype type, Square square);
    Color color; 
    Piecetype type;
    Square square;
};

#endif