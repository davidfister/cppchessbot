#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <list>
#include "move.hpp"
#include "colors.hpp"

class Piece{
public:
    Piece();
    char type;
    Color color; 
    Square square;
    bool set_pos(uint8_t x, uint8_t y);
    bool set_type(char type);
    bool set_color(Color color);
    virtual std::list<Move> all_moves();
};

#endif