#ifndef MOVE_HPP
#define MOVE_HPP

#include "square.hpp"

class Move {
public:
  Move();
  Move(Square start_square, Square end_square);
  Square start_square;
  Square end_square;
}; 

#endif