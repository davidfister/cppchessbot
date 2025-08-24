#include "board.hpp"
#include "pawn.hpp"

void Board::init()
{
    for(uint8_t i = 0; i < 8; i++){
        for(uint8_t j = 0; j < 8; j++){
            board[i][j] = new Piece();
            board[i][j]->set_pos(i,j);
            board[i][j]->set_type('x');
        }
    }
    board[0][1] = new Pawn();
    board[0][1]->set_type('a');
    board[0][1]->set_pos(0,1);
    board[0][1]->set_color(Color::white);
}

std::string Board::testMoves()
{
    std::string t = "";
    for (Move m : board[0][1]->all_moves()){
        t += 'a' + m.start_square.pos_y;
        t += '1' + m.start_square.pos_x;
    
        t += " to ";
        t += 'a' + m.end_square.pos_y;
        t += '1' + m.end_square.pos_x;
    }
    return t;
}

std::string Board::print_board()
{
    std::string board_string = "";
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            board_string += board[i][j]->type;
        }
        board_string += "\n";
    }
    return board_string;
};

std::list<Move> Board::allMoves(){
    
}