#include "board.hpp"
#include "piecetypes.hpp"
#include <iostream>

bool Board::valid_coordinates(int row, int column)
{
    if(column < 0 || column > 7){
        return false;
    }
    if(row < 0 || row > 7){
        return false;
    }
    return true;
}

bool Board::is_valid_dest_square(Square square, Color color_of_moving_piece)
{    
    if(!valid_coordinates(square.row, square.column)){
        return false;
    }

    if(board[square.row][square.column]->type == Piecetype::none){
        return true;
    }

    if(board[square.row][square.column]->color == color_of_moving_piece){
        return false;
    }

    return true;
}

bool Board::is_legal_move(Move move)
{    
    if(!is_valid_dest_square(move.end_square, move.color_moved_piece)){        
        return false;
    }


    if(!mutex_legal_move_check){
        mutex_legal_move_check = true;
        this->do_move(move);

        if(move.color_moved_piece == Color::white){
            for(Move m : this->allMoves()){
                if (m.end_square == whiteKing->square){
                    //std::cout <<"Move not possible:\n" << print_board() << m.start_square.row <<" "<<m.start_square.column <<" "<< m.moved_piece << std::endl;

                    this->undo_move(move);
                    mutex_legal_move_check = false;
                    return false;
                }
            }
        }
        else{
            for(Move m : this->allMoves()){
                if (m.end_square == blackKing->square){
                    this->undo_move(move);
                    mutex_legal_move_check = false;
                    return false;
                }
            }
        }

        this->undo_move(move);
        mutex_legal_move_check = false;
    }

    return true;
}

bool Board::is_legal_nullmove()
{
    this->do_nullmove();
    if(this->color_to_move == Color::black){
        for(Move m : this->allMoves()){
            if (m.end_square == whiteKing->square){
                this->undo_nullmove();

                return false;
            }
        }
    }
    else{
        for(Move m : this->allMoves()){
            if (m.end_square == blackKing->square){
                this->undo_nullmove();

                return false;
            }
        }
    }
    this->undo_nullmove();


    return true;
}

bool Board::is_checkmate()
{
    if(this->allMoves().size() != 0){
        return false;
    }
    return !is_legal_nullmove();
}

bool Board::is_draw()
{
    if(this->allMoves().size() != 0){
        return false;
    }
    
    return is_legal_nullmove();
}

void Board::init()
{   
    Piecetype start_pieces[8][8] = {
                            {Piecetype::rook, Piecetype::knight, Piecetype::bishop, Piecetype::queen, Piecetype::king, Piecetype::bishop, Piecetype::knight, Piecetype::rook},
                            {Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn, Piecetype::pawn},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
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
            board[7-row][column] = new Piece(start_colors[row][column], start_pieces[row][column], Square(7-row,column));
            if(start_pieces[row][column] == Piecetype::king){
                if(start_colors[row][column] == Color::white){
                    whiteKing = board[7-row][column];
                }
                else{
                    blackKing = board[7-row][column];
                }
            }
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
bool Board::do_move(Move move)
{   
    this->captureStack.push_back(board[move.end_square.row][move.end_square.column]);
    board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
    board[move.start_square.row][move.start_square.column] = new Piece(Color::clear, Piecetype::none, Square(move.start_square.row, move.start_square.column));

    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        color_to_move = Color::black;
    }
    board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
    board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;

    return true;
}
bool Board::do_nullmove()
{
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        color_to_move = Color::black;
    }
    return true;
}
bool Board::undo_move(Move move)
{
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        color_to_move = Color::black;
    }
    delete board[move.start_square.row][move.start_square.column];
    board[move.start_square.row][move.start_square.column] = board[move.end_square.row][move.end_square.column];
    board[move.end_square.row][move.end_square.column] = this->captureStack.back();
    this->captureStack.pop_back();

    board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
    board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;

    return true;
}
bool Board::undo_nullmove()
{
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        color_to_move = Color::black;
    }
    return true;
}
bool Board::test_board_coords()
{
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            if(!board[row][column]->square.row == row){
                std::cout << board[row][column]->square.row << std::endl;
                std::cout << board[row][column]->square.column<< std::endl;
                std::cout << row<< std::endl;
                std::cout << column<< std::endl;


                return false;
            }
            else if (!board[row][column]->square.column == column){
                return false;
            }
        }
    }
    return true;
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

            case Piecetype::pawn:
            {
                std::list<Square> possibleSquares{};

                if(this->color_to_move == Color::white){
                    if(board[row][column]->color == this->color_to_move){
                        
                        if(valid_coordinates(row+1, column) && board[row+1][column]->type == Piecetype::none){
                            possibleSquares.push_back(Square(row+1,column));
                        }
                        
                        if(row == 1 && valid_coordinates(row+2, column) && board[row+1][column]->type == Piecetype::none && board[row+2][column]->type == Piecetype::none){
                            possibleSquares.push_back(Square(row+2,column));
                        }

                        if(valid_coordinates(row+1, column+1) && board[row+1][column+1]->type != Piecetype::none){
                            possibleSquares.push_back(Square(row+1,column+1));
                        }
                        if(valid_coordinates(row+1, column-1) && board[row+1][column-1]->type != Piecetype::none){
                            possibleSquares.push_back(Square(row+1,column-1));
                        }
                    }
                }
                else{
                    if(board[row][column]->color == this->color_to_move){
                        if(valid_coordinates(row-1, column) && board[row-1][column]->type == Piecetype::none){
                            possibleSquares.push_back(Square(row-1,column));
                        }
                        
                        if(row == 6 && valid_coordinates(row-2, column)&& board[row-1][column]->type == Piecetype::none && board[row-2][column]->type == Piecetype::none){
                            possibleSquares.push_back(Square(row-2,column));
                        }
                        if(valid_coordinates(row-1, column+1) && board[row-1][column+1]->type != Piecetype::none){
                            possibleSquares.push_back(Square(row-1,column+1));
                        }
                        if(valid_coordinates(row-1, column-1) && board[row-1][column-1]->type != Piecetype::none){
                            possibleSquares.push_back(Square(row-1,column-1));
                        }
                    }   
                }

                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }

            }break;

            //TODO:
            case Piecetype::knight:
            {   
                std::list<Square> possibleSquares{};


                if(board[row][column]->color == this->color_to_move){
                    for(int i = 1; i >= -1; i -= 2){//left/right
                        for(int j = 1; j <= 2; j++){//1 or 2 left/right
                            for(int k = 1; k >= -1; k -= 2){ //up/down
                                possibleSquares.push_back(Square(row - i*j, column + k*(3-j)));
                            }
                        }
                    }
                }
                
                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }
                
            }break;
                
            case Piecetype::bishop:
            {
                std::list<Square> possibleSquares{};

                if(board[row][column]->color == this->color_to_move){
                    int offset = 1;
                    bool direction_top_left = true;
                    bool direction_top_right = true;
                    bool direction_bottom_left = true;
                    bool direction_bottom_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        if(direction_top_left){
                            if(valid_coordinates(row+offset, column-offset) && board[row+offset][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column-offset));
                                direction_top_left = false;
                            }
                        }
                        if(direction_top_right){
                            if(valid_coordinates(row+offset, column+offset) && board[row+offset][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column+offset));
                                direction_top_right = false;
                            }
                        }
                        if(direction_bottom_left){
                            if(valid_coordinates(row-offset, column-offset) && board[row-offset][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column-offset));
                                direction_bottom_left = false;
                            }
                        }
                        if(direction_bottom_right){
                            if(valid_coordinates(row-offset, column+offset) && board[row-offset][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column+offset));
                                direction_bottom_right = false;
                            }
                        }
                        if(!(direction_bottom_left || direction_bottom_right || direction_top_left || direction_top_right)){
                            break;
                        }
                    }
                }

                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }

            }break;
            
            case Piecetype::rook:
            {              
                std::list<Square> possibleSquares{};
                
                if(board[row][column]->color == this->color_to_move){

                    int offset = 1;
                    bool direction_top = true;
                    bool direction_bottom = true;
                    bool direction_left = true;
                    bool direction_right = true;

                    for(int offset = 1; offset <= 7; offset++){
                        if(direction_top){
                            if(valid_coordinates(row+offset, column) && board[row+offset][column]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column));
                                direction_top = false;
                            }

                        }
                        if(direction_bottom){
                            if(valid_coordinates(row-offset, column) && board[row-offset][column]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column));
                                direction_bottom = false;
                            }

                        }
                        if(direction_left){
                            if(valid_coordinates(row, column-offset) && board[row][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row,column-offset));
                                direction_left = false;
                            }

                        }
                        if(direction_right){
                            if(valid_coordinates(row, column+offset) && board[row][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row,column+offset));
                                direction_right = false;
                            }
                        }
                        
                        if(!(direction_bottom || direction_top || direction_left || direction_right)){
                            break;
                        }
                    }
                }

                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }


            }break;
            
            case Piecetype::queen:
            {
                std::list<Square> possibleSquares{};


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
                            if(valid_coordinates(row+offset, column-offset) && board[row+offset][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column-offset));
                                direction_top_left = false;
                            }
                        }
                        if(direction_top_right){
                            if(valid_coordinates(row+offset, column+offset) && board[row+offset][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column+offset));
                                direction_top_right = false;
                            }
                        }
                        if(direction_bottom_left){
                            if(valid_coordinates(row-offset, column-offset) && board[row-offset][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column-offset));
                                direction_bottom_left = false;
                            }
                        }
                        if(direction_bottom_right){
                            if(valid_coordinates(row-offset, column+offset) && board[row-offset][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column+offset));
                                direction_bottom_right = false;
                            }
                        }
                        if(direction_top){

                            if(valid_coordinates(row+offset, column) && board[row+offset][column]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column));
                            }
                            else{
                                possibleSquares.push_back(Square(row+offset,column));
                                direction_top = false;
                            }

                        }
                        if(direction_bottom){
                            if(valid_coordinates(row-offset, column) && board[row-offset][column]->color == Color::clear){
                                possibleSquares.push_back(Square(row-offset,column));
                            }
                            else{
                                possibleSquares.push_back(Square(row-offset,column));
                                direction_bottom = false;
                            }

                        }
                        if(direction_left){
                            if(valid_coordinates(row, column-offset) && board[row][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row,column-offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row,column-offset));
                                direction_left = false;
                            }

                        }
                        if(direction_right){
                            if(valid_coordinates(row, column+offset) && board[row][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row,column+offset));
                            }
                            else{
                                possibleSquares.push_back(Square(row,column+offset));
                                direction_right = false;
                            }
                        }
                        
                        if(!(direction_bottom_left || direction_bottom_right || direction_top_left || direction_top_right || direction_bottom || direction_top || direction_left || direction_right)){
                            break;
                        }
                    }
                }
                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }

            }break;
            //TODO:
            // - castle
            // - check
            // - checkmate
            case Piecetype::king:
            {
                std::list<Square> possibleSquares{};
                if(board[row][column]->color == this->color_to_move){
                    possibleSquares.push_back(Square(row-1,column-1));
                    possibleSquares.push_back(Square(row-1,column));
                    possibleSquares.push_back(Square(row-1,column+1));
                    possibleSquares.push_back(Square(row,column-1));
                    possibleSquares.push_back(Square(row,column+1));
                    possibleSquares.push_back(Square(row+1,column-1));
                    possibleSquares.push_back(Square(row+1,column));
                    possibleSquares.push_back(Square(row+1,column+1));

                }

                Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[currentSquare.row][currentSquare.column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        all_moves.push_back(m);
                    }
                }

            }break;

            default:
                break;
                
            }
            }   
        }

    return all_moves;
}