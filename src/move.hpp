#ifndef MOVE_HPP
#define MOVE_HPP

#include "square.hpp"
#include "colors.hpp"
#include "piecetypes.hpp"
#include <string>

class Move {
public:
  Move();
  Move(std::string s, Color color_moved_piece);
  Move(Square start_square, Square end_square, Color color_moved_piece, Piecetype moved_piece, Piecetype captured_piece);
  Square start_square;
  Square end_square;
  Piecetype moved_piece;
  Piecetype captured_piece;
  Color color_moved_piece;
  bool is_castle;
  bool is_en_passant;
  bool is_capture;
  void print_move();
  std::string to_string();
}; 

#endif