#include "board.hpp"
#include "piecetypes.hpp"
#include <iostream>

bool Board::valid_coordinates(int row, int column)
{
    benchmark_calls_valid_coordinates++;
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
    benchmark_calls_is_valid_dest_square++;
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
    benchmark_calls_valid_is_legal_move++;
    if(!is_valid_dest_square(move.end_square, move.color_moved_piece)){        
        return false;
    }
    this->do_move(move);

    Square s = Square();
    Piece* currentKing;
    if(move.color_moved_piece == Color::white){
        currentKing = whiteKing;
        s.row = whiteKing->square.row + 1;
        s.column = whiteKing->square.column - 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_move(move);
            return false;
        }
        s.column = whiteKing->square.column + 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_move(move);
            return false;
        }
    }
    else{
        currentKing = blackKing;
        s.row = blackKing->square.row - 1;
        s.column = blackKing->square.column - 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_move(move);
            return false;
        }
        s.column = blackKing->square.column + 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_move(move);
            return false;
        }
    }


    //Check if Knights
    for(int i = 1; i >= -1; i -= 2){//left/right
        for(int j = 1; j <= 2; j++){//1 or 2 left/right
            for(int k = 1; k >= -1; k -= 2){ //up/down
                s.row = currentKing->square.row -i*j;
                s.column = currentKing->square.column + k*(3-j);
                if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == knight){
                    this->undo_move(move);
                    return false;
                }
            }
        }
    }
    

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
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_top_left = false;
                }
            }
        }
        if(direction_top){
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_top = false;
                }
            }
        }
        if(direction_top_right){
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_top_right = false;
                }
            }
        }
        if(direction_right){
            s.row = currentKing->square.row;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_right = false;
                }
            }
        }
        if(direction_bottom_right){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_bottom_right = false;
                }
            }
        }
        if(direction_bottom){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_bottom = false;
                }
            }
        }
        if(direction_bottom_left){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_bottom_left = false;
                }
            }
        }
        if(direction_left){
            s.row = currentKing->square.row;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_move(move);
                    return false;
                }
                else{
                    direction_left = false;
                }
            }
        }
        
    }   
    this->undo_move(move);
    return true;

}

bool Board::is_legal_nullmove() // FIX!!!!!
{
    benchmark_calls_valid_is_legal_nullmove++;
    Square s = Square();
    Piece* currentKing;
    this->do_nullmove();
    if(this->color_to_move == Color::black){
        currentKing = whiteKing;
        s.row = whiteKing->square.row + 1;
        s.column = whiteKing->square.column - 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_nullmove();
            return false;
        }
        s.column = whiteKing->square.column + 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_nullmove();
            return false;
        }
    }
    else{
        currentKing = blackKing;
        s.row = blackKing->square.row - 1;
        s.column = blackKing->square.column - 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_nullmove();
            return false;
        }
        s.column = blackKing->square.column + 1;
        if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == Piecetype::pawn){
            this->undo_nullmove();
            return false;
        }
    }


    //Check if Knights
    for(int i = 1; i >= -1; i -= 2){//left/right
        for(int j = 1; j <= 2; j++){//1 or 2 left/right
            for(int k = 1; k >= -1; k -= 2){ //up/down
                s.row = currentKing->square.row -i*j;
                s.column = currentKing->square.column + k*(3-j);
                if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type == knight){
                    this->undo_nullmove();
                    return false;
                }
            }
        }
    }
    

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
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_top_left = false;
                }
            }
        }
        if(direction_top){
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_top = false;
                }
            }
        }
        if(direction_top_right){
            s.row = currentKing->square.row + offset;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_top_right = false;
                }
            }
        }
        if(direction_right){
            s.row = currentKing->square.row;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_right = false;
                }
            }
        }
        if(direction_bottom_right){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column + offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::bishop){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_bottom_right = false;
                }
            }
        }
        if(direction_bottom){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_bottom = false;
                }
            }
        }
        if(direction_bottom_left){
            s.row = currentKing->square.row - offset;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_bottom_left = false;
                }
            }
        }
        if(direction_left){
            s.row = currentKing->square.row;
            s.column = currentKing->square.column - offset;
            if(valid_coordinates(s.row,s.column) && board[s.row][s.column]->color == this->color_to_move && board[s.row][s.column]->type != Piecetype::none){
                if(board[s.row][s.column]->type == Piecetype::queen || board[s.row][s.column]->type == Piecetype::rook){
                    this->undo_nullmove();
                    return false;
                }
                else{
                    direction_left = false;
                }
            }
        }
        
    }   
    this->undo_nullmove();
    return true;
}

bool Board::is_checkmate()
{
    benchmark_calls_is_checkmate++;
    if(is_legal_nullmove()){
        return false;
    }
    
    std::list<Move>* moves = new std::list<Move>;

    if(this->allMoves(moves)->size() != 0){
        delete moves;
        return false;
    }
    delete moves;
    return true;
}

bool Board::is_draw()
{
    benchmark_calls_is_draw++;

    std::list<Move>* moves = new std::list<Move>;

    if(this->allMoves(moves)->size() != 0){
        delete moves;
        return false;
    }
    delete moves;
    return is_legal_nullmove();
}

void Board::init()
{   
    benchmark_ms = std::chrono::milliseconds(0);

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

    Piecetype simple_start_pieces[8][8] = {
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::king, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::rook},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::queen, Piecetype::king, Piecetype::rook, Piecetype::none, Piecetype::none}
                            };
    Color simple_start_colors[8][8] = {
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::black, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::white},
                            {Color::clear, Color::clear, Color::clear, Color::white, Color::white, Color::white, Color::clear, Color::clear}
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
    benchmark_calls_do_move++;
    this->captureStack.push_back(board[move.end_square.row][move.end_square.column]);
    board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
    board[move.start_square.row][move.start_square.column] = new Piece(Color::clear, Piecetype::none, Square(move.start_square.row, move.start_square.column));

    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }
    board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
    board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
    

    
    return true;
}

bool Board::do_nullmove()
{
    benchmark_calls_do_nullmove++;
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }

    return true;
}

bool Board::undo_move(Move move)
{
    benchmark_calls_undo_move++;
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
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
    benchmark_calls_undo_nullmove++;
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }
  
    return true;
}

std::list<Move> *Board::allMoves(std::list<Move> *allMovesList){
    auto t1 = std::chrono::high_resolution_clock::now();
    benchmark_calls_allMoves++;

    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++)
        {
            std::list<Square> possibleSquares{};

            switch (board[row][column]->type)
            {


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
            } break;

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
            }break;

//TODO:
            case Piecetype::knight:
            {   
                if(board[row][column]->color == this->color_to_move){
                    for(int i = 1; i >= -1; i -= 2){//left/right
                        for(int j = 1; j <= 2; j++){//1 or 2 left/right
                            for(int k = 1; k >= -1; k -= 2){ //up/down
                                if(valid_coordinates(row - i*j, column + k*(3-j))){
                                    possibleSquares.push_back(Square(row - i*j, column + k*(3-j)));
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
                            if(valid_coordinates(row+offset, column-offset) && board[row+offset][column-offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column-offset));
                            }
                            else{
                                if(valid_coordinates(row+offset, column-offset)){
                                    possibleSquares.push_back(Square(row+offset,column-offset));
                                }
                                direction_top_left = false;
                            }
                        }
                        if(direction_top_right){
                            if(valid_coordinates(row+offset, column+offset) && board[row+offset][column+offset]->color == Color::clear){
                                possibleSquares.push_back(Square(row+offset,column+offset));
                            }
                            else{
                                if(valid_coordinates(row+offset, column+offset)){
                                    possibleSquares.push_back(Square(row+offset,column-offset));
                                }
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

            }break;

            //TODO:
            // - en passsant
            case Piecetype::pawn:
            {
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

            }break;

            
            
            
            
           
            //TODO:
            // - castle
            // - check
            // - checkmate
            case Piecetype::king:
            {
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

            }break;

            default:
                break;
                
            }

            Square currentSquare = Square(row, column);
                for (Square  s : possibleSquares){
                    if(!valid_coordinates(s.row,s.column)){
                        continue;
                    }
                    Move m = Move(currentSquare, s, this->color_to_move, board[row][column]->type, board[s.row][s.column]->type);

                    if(is_legal_move(m)){
                        if(m.is_capture == true){
                            allMovesList->push_front(m);
                        }
                        else{
                            allMovesList->push_back(m);
                        }
                    }
                }
            }   
        }
    

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    this->benchmark_ms += ms_int;
    return allMovesList;
}