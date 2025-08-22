#include "board.hpp"

void Board::init()
{
    for(uint8_t i = 0; i < 8; i++){
        for(uint8_t j = 0; j < 8; j++){
            board[i][j] = Piece();
            board[i][j].set_pos(i,j);
            board[i][j].set_type('x');
        }
    }
    board[0][1].set_type('A');
}

std::string Board::print_board()
{
    std::string board_string = "";
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            board_string += board[i][j].type;
        }
        board_string += "\n";
    }
    return board_string;
};