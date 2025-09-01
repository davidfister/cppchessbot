#include "board.hpp"
#include "piecetypes.hpp"
#include <iostream>

bool Board::is_valid_dest_square(int row, int column, Color color)
{
    if(column < 0 || column > 7){
        return false;
    }
    if(row < 0 || row > 7){
        return false;
    }
    if(board[row][column]->type == Piecetype::none){
        return true;
    }
    if(board[row][column]->color == color){
        return false;
    }
    return true;
}

void Board::init()
{   
    Piecetype start_pieces[8][8] = {
                            {Piecetype::rook, Piecetype::knight, Piecetype::bishop, Piecetype::queen, Piecetype::king, Piecetype::bishop, Piecetype::knight, Piecetype::rook},
                            {Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn},
                            {Piecetype::none, Piecetype::none, Piecetype::bishop, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::bishop, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn},
                            {Piecetype::rook, Piecetype::knight, Piecetype::bishop, Piecetype::queen, Piecetype::king, Piecetype::bishop, Piecetype::knight, Piecetype::rook}
                            };
    Color start_colors[8][8] = {
                            {Color::black, Color::black, Color::black, Color::black, Color::black, Color::black, Color::black, Color::black},
                            {Color::black, Color::black, Color::black, Color::black, Color::black, Color::black, Color::black, Color::black},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::white, Color::white, Color::white, Color::white, Color::white, Color::white, Color::white, Color::white},
                            {Color::white, Color::white, Color::white, Color::white, Color::white, Color::white, Color::white, Color::white}
                            };


    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            board[7-row][column] = new Piece(start_colors[row][column], start_pieces[row][column]);
        }
    }
}

std::string Board::print_board()
{
    std::string board_string = "";
    
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            char offset = 0;
            if(board[i][j]->color == Color::black){
                offset = ('a' - 'A');
            }
            switch(board[i][j]->type){
                case Piecetype::pawn:
                    board_string += 'p' - offset;
                break;
                case Piecetype::knight:
                    board_string += 'n' - offset;
                break;
                case Piecetype::bishop:
                    board_string += 'b' - offset;
                break;
                case Piecetype::rook:
                    board_string += 'r' - offset;
                break;
                case Piecetype::queen:
                    board_string += 'q' - offset;
                break;
                case Piecetype::king:
                    board_string += 'k' - offset;
                break;
                default:
                    board_string += '_';
                break;

            };
        }
        board_string += "\n";
    }
    return board_string;
}
std::string Board::do_move(Move move)
{   
    std::cout<<"Doing move: ";
    move.print_move();
    delete board[move.end_square.row][move.end_square.column];
    board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
    board[move.start_square.row][move.start_square.column] = new Piece(Color::clear, Piecetype::none);
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        color_to_move = Color::black;
    }
    return "";
};

std::list<Move> Board::allMoves(){
    std::list<Move> all_moves{}; //speedup if change to reference based?
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            switch (board[row][column]->type)
            {
            //TODO:
            // - en passsant
            // - capture
            // - different for each side
            case Piecetype::pawn: 
                if(board[row][column]->color == this->color_to_move){
                    if(is_valid_dest_square(row+1, column, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row+1,column)));
                    }
                    if(row == 1 && is_valid_dest_square(row+2, column, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row+2,column)));
                    }
                }
                break;
            //TODO:
            case Piecetype::knight:
                {   
                if(board[row][column]->color == this->color_to_move){
                    for(int i = 1; i >= -1; i -= 2){//left/right
                        for(int j = 1; j <= 2; j++){//1 or 2 left/right
                            for(int k = 1; k >= -1; k -= 2){ //up/down
                                if(is_valid_dest_square(row - i*j, column + k*(3-j),board[row][column]->color)){
                                    all_moves.push_front(Move(Square(row,column),Square(row - i*j, column + k*(3-j))));//changepushback
                                }
                            }
                        }
                    }
                }
                
                
                }break;
            case Piecetype::bishop:
                {
                if(board[row][column]->color == this->color_to_move){
                    int offset = 1;
                    bool direction_top_left = true;
                    bool direction_top_right = true;
                    bool direction_bottom_left = true;
                    bool direction_bottom_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        if(direction_top_left){
                            if(is_valid_dest_square(row+offset,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column-offset)));
                            }
                            else{
                                direction_top_left = false;
                            }
                        }
                        if(direction_top_right){
                            if(is_valid_dest_square(row+offset,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column+offset)));
                            }
                            else{
                                direction_top_right = false;
                            }
                        }
                        if(direction_bottom_left){
                            if(is_valid_dest_square(row-offset,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column-offset)));
                            }
                            else{
                                direction_bottom_left = false;
                            }
                        }
                        if(direction_bottom_right){
                            if(is_valid_dest_square(row-offset,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column+offset)));
                            }
                            else{
                                direction_bottom_right = false;
                            }
                        }
                        if(!(direction_bottom_left || direction_bottom_right || direction_top_left || direction_top_right)){
                            break;
                        }
                    }
                }
                }break;
            
            case Piecetype::rook:
                {
                if(board[row][column]->color == this->color_to_move){

                    int offset = 1;
                    bool direction_top = true;
                    bool direction_bottom = true;
                    bool direction_left = true;
                    bool direction_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        if(direction_top){
                            if(is_valid_dest_square(row+offset,column, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column)));
                            }
                            else{
                                direction_top = false;
                            }
                        }
                        if(direction_bottom){
                            if(is_valid_dest_square(row-offset,column, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column)));
                            }
                            else{
                                direction_bottom = false;
                            }
                        }
                        if(direction_left){
                            if(is_valid_dest_square(row,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row,column-offset)));
                            }
                            else{
                                direction_left = false;
                            }
                        }
                        if(direction_right){
                            if(is_valid_dest_square(row,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row,column+offset)));
                            }
                            else{
                                direction_right = false;
                            }
                        }
                        if(!(direction_bottom || direction_top || direction_left || direction_right)){
                            break;
                        }
                    }
                }

                }break;
            case Piecetype::queen:
                {
                if(board[row][column]->color == this->color_to_move){
                    int offset = 1;
                    bool direction_top_left = true;
                    bool direction_top_right = true;
                    bool direction_bottom_left = true;
                    bool direction_bottom_right = true;
                    bool direction_top = true;
                    bool direction_bottom = true;
                    bool direction_left = true;
                    bool direction_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        if(direction_top_left){
                            if(is_valid_dest_square(row+offset,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column-offset)));
                            }
                            else{
                                direction_top_left = false;
                            }
                        }
                        if(direction_top_right){
                            if(is_valid_dest_square(row+offset,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column+offset)));
                            }
                            else{
                                direction_top_right = false;
                            }
                        }
                        if(direction_bottom_left){
                            if(is_valid_dest_square(row-offset,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column-offset)));
                            }
                            else{
                                direction_bottom_left = false;
                            }
                        }
                        if(direction_bottom_right){
                            if(is_valid_dest_square(row-offset,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column+offset)));
                            }
                            else{
                                direction_bottom_right = false;
                            }
                        }
                        if(direction_top){
                            if(is_valid_dest_square(row+offset,column, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row+offset,column)));
                            }
                            else{
                                direction_top = false;
                            }
                        }
                        if(direction_bottom){
                            if(is_valid_dest_square(row-offset,column, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row-offset,column)));
                            }
                            else{
                                direction_bottom = false;
                            }
                        }
                        if(direction_left){
                            if(is_valid_dest_square(row,column-offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row,column-offset)));
                            }
                            else{
                                direction_left = false;
                            }
                        }
                        if(direction_right){
                            if(is_valid_dest_square(row,column+offset, board[row][column]->color)){
                                all_moves.push_back(Move(Square(row,column),Square(row,column+offset)));
                            }
                            else{
                                direction_right = false;
                            }
                        }
                        
                        if(!(direction_bottom_left || direction_bottom_right || direction_top_left || direction_top_right || direction_bottom || direction_top || direction_left || direction_right)){
                            break;
                        }
                    }
                }

                }break;
            //TODO:
            // - castle
            // - check
            // - checkmate
            case Piecetype::king:
                if(board[row][column]->color == this->color_to_move){
                    if(is_valid_dest_square(row+1,column-1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row+1,column-1)));
                    }
                    
                    if(is_valid_dest_square(row+1,column+1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row+1,column+1)));
                    }
                
                    if(is_valid_dest_square(row-1,column-1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row-1,column-1)));
                    }
                
                    if(is_valid_dest_square(row-1,column+1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row-1,column+1)));
                    }
                
                    if(is_valid_dest_square(row+1,column, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row+1,column)));
                    }

                    if(is_valid_dest_square(row-1,column, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row-1,column)));
                    }
            
                    if(is_valid_dest_square(row,column-1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row,column-1)));
                    }
                    
                    if(is_valid_dest_square(row,column+1, board[row][column]->color)){
                        all_moves.push_back(Move(Square(row,column),Square(row,column+1)));
                    }
                    break;
                
                default:
                    break;
                }
            }
        }
    }
    return all_moves;
}