//Start by generating a slow but working move generator. Initial idea is using array based representation of the board with classes for each piece. 
//After implementing i will probably switch to bitboards or some other board representation. 
#ifndef BOARD_HPP
#define BOARD_HPP


#include"piece.hpp"
#include <string>
#include <chrono>


class Board
{
    std::list<Piece*> captureStack;
 
    Piece* whiteKing;
    Piece* blackKing;

    

    bool en_passant_possible;
    Square en_passant_square;


//TODO: For benchmark reasons all functions public. Undo
public:
    void init();
        
    std::list<Move>* allMoves(std::list<Move>* allMovesList);
    std::string print_board();

    bool do_uci_move(std::string s);


    bool do_move(Move move);
    bool do_nullmove();
    bool undo_move(Move move);
    bool undo_nullmove();

    bool is_square_attacked(Square s, Color attackedColor);
    bool is_checkmate();
    bool is_draw();


    bool valid_coordinates(int row, int column);
    bool is_valid_dest_square(int row, int column, Color color_of_moving_piece);
    bool is_legal_move(Move move);
    bool is_legal_nullmove();

    Color color_to_move = Color::white;
    bool is_white_castled = false;
    bool is_black_castled = false;

    int ply = 0;
    int ply_white_king_moved = -1;
    int ply_black_king_moved = -1;
    int ply_white_a_rook_moved = -1;
    int ply_white_h_rook_moved = -1;
    int ply_black_a_rook_moved = -1;
    int ply_black_h_rook_moved = -1;

    Piece* board[8][8]; //[row]][column]
    
    //benchmark
    long benchmark_calls_allMoves = 0;
    long benchmark_calls_do_move = 0;
    long benchmark_calls_do_nullmove = 0;
    long benchmark_calls_undo_move = 0;
    long benchmark_calls_undo_nullmove = 0;
    long benchmark_calls_is_checkmate = 0;
    long benchmark_calls_is_draw = 0;
    long benchmark_calls_is_square_attacked = 0;
    long benchmark_calls_valid_coordinates = 0;
    long benchmark_calls_is_valid_dest_square = 0;
    long benchmark_calls_is_legal_move = 0;
    long benchmark_calls_is_legal_nullmove = 0;


    std::chrono::nanoseconds benchmark_ms;
};

#endif