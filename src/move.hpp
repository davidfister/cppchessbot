#ifndef MOVE_HPP
#define MOVE_HPP

#include "square.hpp"
#include "colors.hpp"
#include "piecetypes.hpp"
#include <string>

class Move {
public:
  Move();
  Move(Square start_square, Square end_square, Color color_moved_piece, Piecetype moved_piece, Piecetype captured_piece);
  Square start_square;
  Square end_square;
  Piecetype moved_piece;
  Piecetype captured_piece;
  Color color_moved_piece;
  bool is_castle;
  bool is_en_passant;
  bool is_capture;
  bool is_promotion;
  void print_move();
  std::string to_string();
}; 

#endif