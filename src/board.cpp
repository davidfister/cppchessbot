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

bool Board::is_valid_dest_square(int row, int column, Color color_of_moving_piece)
{    
    benchmark_calls_is_valid_dest_square++;

    if(board[row][column]->type == Piecetype::none){
        return true;
    }

    if(board[row][column]->color == color_of_moving_piece){
        return false;
    }

    return true;
}

bool Board::is_legal_move(Move move)
{    
    benchmark_calls_valid_is_legal_move++;
    Piece* currentKing = color_to_move == Color::white ? whiteKing : blackKing;

    this->do_move(move);
    bool is_legal = !is_square_attacked(currentKing->square, currentKing->color);
    if(move.moved_piece == Piecetype::king){
        if(abs(blackKing->square.row - whiteKing->square.row) <= 1 && abs(blackKing->square.column - whiteKing->square.column)<= 1){
            is_legal = false;
        }
    }
    this->undo_move(move);
    return is_legal;
}

bool Board::is_legal_nullmove()
{
    benchmark_calls_valid_is_legal_nullmove++;
    Piece* currentKing = this->color_to_move == Color::white ? whiteKing : blackKing;

    this->do_nullmove();
    bool a = is_square_attacked(currentKing->square, currentKing->color);   
    this->undo_nullmove();
    return !a;
}

bool Board::is_square_attacked(Square s, Color attackedColor)
{
    int dest_row;
    int dest_column;
    Color attackingColor;
    if(attackedColor == Color::white){
        attackingColor = Color::black;
        dest_row = s.row + 1;
        dest_column = s.column - 1;
        if(valid_coordinates(dest_row,dest_column) && board[dest_row][dest_column]->color == attackingColor && board[dest_row][dest_column]->type == Piecetype::pawn){
            return true;
        }
        dest_column = s.column + 1;
        if(valid_coordinates(dest_row,dest_column) && board[dest_row][dest_column]->color == attackingColor && board[dest_row][dest_column]->type == Piecetype::pawn){
            return true;
        }
    }
    else{
        attackingColor = Color::white;

        dest_row = s.row - 1;
        dest_column = s.column - 1;
        if(valid_coordinates(dest_row,dest_column) && board[dest_row][dest_column]->color == attackingColor && board[dest_row][dest_column]->type == Piecetype::pawn){
            return true;
        }
        dest_column = s.column + 1;
        if(valid_coordinates(dest_row,dest_column) && board[dest_row][dest_column]->color == attackingColor && board[dest_row][dest_column]->type == Piecetype::pawn){
            return true;
        }
    }


    //Check if Knights
    for(int i = 1; i >= -1; i -= 2){//left/right
        for(int j = 1; j <= 2; j++){//1 or 2 left/right
            for(int k = 1; k >= -1; k -= 2){ //up/down
                dest_row = s.row -i*j;
                dest_column = s.column + k*(3-j);
                if(valid_coordinates(dest_row,dest_column) && board[dest_row][dest_column]->color == attackingColor && board[dest_row][dest_column]->type == knight){
                    return true;
                }
            }
        }
    }
    
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
            dest_row = s.row + offset;
            dest_column = s.column - offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::bishop)){
                        return true;
                    }
                    direction_top_left = false;
                }
            }
            else{
                direction_top_left = false;
            }
        }

        if(direction_top){
            dest_row = s.row + offset;
            dest_column = s.column;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::rook)){
                        return true;
                    }
                    direction_top = false;
                }
            }
            else{
                direction_top = false;
            }
        }
        if(direction_top_right){
            dest_row = s.row + offset;
            dest_column = s.column + offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::bishop)){
                        return true;
                    }
                    direction_top_right = false;
                }
            }
            else{
                direction_top_right = false;
            }
        }
        if(direction_right){
            dest_row = s.row;
            dest_column = s.column + offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::rook)){
                        return true;
                    }
                    direction_right = false;
                }
            }
            else{
                direction_right = false;
            }
        }
        if(direction_bottom_right){
            dest_row = s.row - offset;
            dest_column = s.column + offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::bishop)){
                        return true;
                    }
                    direction_bottom_right = false;
                }
            }
            else{
                direction_bottom_right = false;
            }
        }
        if(direction_bottom){
            dest_row = s.row - offset;
            dest_column = s.column;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::rook)){
                        return true;
                    }
                    direction_bottom = false;
                }
            }
            else{
                direction_bottom = false;
            }
        }
        if(direction_bottom_left){
            dest_row = s.row - offset;
            dest_column = s.column - offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::bishop)){
                        return true;
                    }
                    direction_bottom_left = false;
                }
            }
            else{
                direction_bottom_left = false;
            }
        }
        if(direction_left){
            dest_row = s.row;
            dest_column = s.column - offset;
            if(valid_coordinates(dest_row,dest_column)){
                if(board[dest_row][dest_column]->type != Piecetype::none){
                    if(board[dest_row][dest_column]->color == attackingColor && (board[dest_row][dest_column]->type == Piecetype::queen || board[dest_row][dest_column]->type == Piecetype::rook)){
                        return true;
                    }
                    direction_left = false;
                }
            }
            else{
                direction_left = false;
            }
        }
    }
    return false;
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

    //Piece* currentKing = this->color_to_move == Color::white ? whiteKing : blackKing;
    /*int row;
    int col;
    for(int r = 1 ; r <= -1; r--){
        for(int c = -1; c >= 1; c++){
            row = currentKing->square.row + r;
            col = currentKing->square.column + c;
            if(valid_coordinates(row,col)){
                Square s{row,col};
                if(is_square_attacked(s, this->color_to_move)){

                }
            }
        }
    }*/
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
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::rook, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::queen, Piecetype::none, Piecetype::none, Piecetype::none},
                            {Piecetype::none, Piecetype::none, Piecetype::none, Piecetype::rook, Piecetype::king, Piecetype::rook, Piecetype::none, Piecetype::none}
                            };
    Color simple_start_colors[8][8] = {
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::black, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::black, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear, Color::clear},
                            {Color::clear, Color::clear, Color::clear, Color::clear, Color::black, Color::clear, Color::clear, Color::clear},
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

bool Board::do_uci_move(std::string s)
{
    Square start_square = Square(-((int)'1' - s.at(1)),-((int)'a' - s.at(0)));
    Square end_square = Square(-((int)'1' - s.at(3)),-((int)'a' - s.at(2)));
    
    Move m = Move(start_square, end_square, color_to_move, board[start_square.row][start_square.column]->type, board[end_square.row][end_square.column]->type);
    this->do_move(m);
    std::cout<<s << std::endl;
    return true;
}

bool Board::do_move(Move move)
{   
    benchmark_calls_do_move++;
    
    this->ply++;
    
    this->captureStack.push_back(board[move.end_square.row][move.end_square.column]);
    board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
    board[move.start_square.row][move.start_square.column] = new Piece(Color::clear, Piecetype::none, Square(move.start_square.row, move.start_square.column));

    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }

    if(move.moved_piece == Piecetype::rook){
        if(move.color_moved_piece == Color::white){
            if(ply_white_a_rook_moved == -1){
                if(move.start_square.column == 0){
                    this->ply_white_a_rook_moved = this->ply;
                }
            }
            if(ply_white_h_rook_moved == -1){
                if(move.start_square.column == 7){
                    this->ply_white_h_rook_moved = this->ply;
                } 
            }
        }
        else{
            if(ply_black_a_rook_moved == -1){
                if(move.start_square.column == 0){
                    this->ply_black_a_rook_moved = this->ply;
                }
            }
            if(ply_black_h_rook_moved == -1){
                if(move.start_square.column == 7){
                    this->ply_black_h_rook_moved = this->ply;
                } 
            }
        }
    }
    if(move.moved_piece == Piecetype::king){
        if(move.color_moved_piece == Color::white){
            ply_white_king_moved = ply;
        }
        else{
            ply_black_king_moved = ply;
        }
    }

    if(move.is_promotion){
        delete board[move.end_square.row][move.end_square.column];
        board[move.end_square.row][move.end_square.column] = new Piece(move.color_moved_piece, Piecetype::queen, Square(move.end_square.row, move.end_square.column));
    }

    if(move.is_en_passant){
        if(move.color_moved_piece == Color::white){
            this->captureStack.push_back(board[move.end_square.row+1][move.end_square.column]);
            board[move.end_square.row-1][move.end_square.column] = new Piece(Color::clear, Piecetype::none, Square(move.end_square.row-1, move.end_square.column));
        }
        else{
            this->captureStack.push_back(board[move.end_square.row-1][move.end_square.column]);
            board[move.end_square.row+1][move.end_square.column] = new Piece(Color::clear, Piecetype::none, Square(move.end_square.row+1, move.end_square.column));
        }
    }

    if(move.is_castle){
        if(move.end_square.column == 6){
            Piece* r = board[move.end_square.row][7];
            board[move.end_square.row][7] = board[move.end_square.row][5];
            board[move.end_square.row][5] = r;
        }
        else{
            Piece* r = board[move.end_square.row][0];
            board[move.end_square.row][0] = board[move.end_square.row][3];
            board[move.end_square.row][3] = r;
        }
        if(move.color_moved_piece == Color::white){
            ply_white_a_rook_moved = ply;
            ply_white_h_rook_moved = ply;
            ply_white_king_moved = ply;
            is_white_castled = true;
        }
        else{
            ply_black_a_rook_moved = ply;
            ply_black_h_rook_moved = ply;
            ply_black_king_moved = ply;
            is_black_castled = true;
        }
    }

    board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
    board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
    

    
    return true;
}

bool Board::do_nullmove()
{
    this->ply++;
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

    if(move.is_promotion){
        delete board[move.start_square.row][move.start_square.column];
        board[move.start_square.row][move.start_square.column] = new Piece(move.color_moved_piece, Piecetype::pawn, Square(move.start_square.row, move.start_square.column));
    }
    if(move.is_en_passant){
        if(move.color_moved_piece == Color::white){
            delete board[move.end_square.row+1 ][move.end_square.column];
            board[move.end_square.row+1][move.end_square.column] = this->captureStack.back();
        }
        else{
            delete board[move.end_square.row-1 ][move.end_square.column];
            board[move.end_square.row-1][move.end_square.column] = this->captureStack.back();        
        }
    }
    if(move.is_castle){
        if(move.end_square.column == 6){
            Piece* r = board[move.end_square.row][5];
            board[move.end_square.row][5] = board[move.end_square.row][7];
            board[move.end_square.row][7] = r;
        }
        else{
            Piece* r = board[move.end_square.row][3];
            board[move.end_square.row][3] = board[move.end_square.row][0];
            board[move.end_square.row][0] = r;
        }
        if(move.color_moved_piece == Color::white){
            is_white_castled = false;
        }
        else{
            is_black_castled = false;
        }
    }
    if(ply_white_king_moved == ply){
        ply_white_king_moved = -1;
    }
    if(ply_black_king_moved == ply){
        ply_black_king_moved = -1;
    }    
    if(ply_white_a_rook_moved == ply){
        ply_white_a_rook_moved = -1;
    }
    if(ply_black_a_rook_moved == ply){
        ply_black_a_rook_moved = -1;
    }
    if(ply_white_h_rook_moved == ply){
        ply_white_h_rook_moved = -1;
    }
    if(ply_black_h_rook_moved == ply){
        ply_black_h_rook_moved = -1;
    }


    board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
    board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;

    this->ply--;
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
    this->ply--;
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
                    bool direction_top_left = true;
                    bool direction_top_right = true;
                    bool direction_bottom_left = true;
                    bool direction_bottom_right = true;
                    bool direction_top = true;
                    bool direction_bottom = true;
                    bool direction_left = true;
                    bool direction_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        int dest_row;
                        int dest_column; 
                        if(direction_top_left){
                            dest_row = row+offset;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top_left = false;
                                    }
                                }
                                else{
                                    direction_top_left = false;
                                }
                            }
                            else{
                                direction_top_left = false;
                            }
                        }

                        if(direction_top_right){
                           dest_row = row+offset;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top_right = false;
                                    }
                                }
                                else{
                                    direction_top_right = false;
                                }

                            }
                            else{
                                direction_top_right = false;
                            }
                        }

                        if(direction_bottom_left){
                          dest_row = row-offset;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom_left = false;
                                    }
                                }
                                else{
                                    direction_bottom_left = false;
                                }

                            }
                            else{
                                direction_bottom_left = false;
                            }  
                        }

                        if(direction_bottom_right){
                            dest_row = row-offset;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom_right = false;
                                    }
                                }
                                else{
                                    direction_bottom_right = false;
                                }

                            }
                            else{
                                direction_bottom_right = false;
                            }
                        }
                        
                        if(direction_top){
                            dest_row = row+offset;
                            dest_column = column;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top = false;
                                    }
                                }
                                else{
                                    direction_top = false;
                                }

                            }
                            else{
                                direction_top = false;
                            }
                        }
                        
                        if(direction_bottom){
                            dest_row = row-offset;
                            dest_column = column;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom = false;
                                    }
                                }
                                else{
                                    direction_bottom = false;
                                }

                            }
                            else{
                                direction_bottom = false;
                            }
                        }
                        
                        if(direction_left){
                            dest_row = row;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_left = false;
                                    }
                                }
                                else{
                                    direction_left = false;
                                }

                            }
                            else{
                                direction_left = false;
                            }
                        }
                        
                        if(direction_right){
                            dest_row = row;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_right = false;
                                    }
                                }
                                else{
                                    direction_right = false;
                                }

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
            } break;

            case Piecetype::rook:
            {                              
                if(board[row][column]->color == this->color_to_move){
                    bool direction_top = true;
                    bool direction_bottom = true;
                    bool direction_left = true;
                    bool direction_right = true;

                    for(int offset = 1; offset <= 7; offset++){
                        int dest_row;
                        int dest_column; 
                        
                        if(direction_top){
                            dest_row = row+offset;
                            dest_column = column;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top = false;
                                    }
                                }
                                else{
                                    direction_top = false;
                                }

                            }
                            else{
                                direction_top = false;
                            }
                        }
                        
                        if(direction_bottom){
                            dest_row = row-offset;
                            dest_column = column;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom = false;
                                    }
                                }
                                else{
                                    direction_bottom = false;
                                }

                            }
                            else{
                                direction_bottom = false;
                            }
                        }
                        
                        if(direction_left){
                            dest_row = row;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_left = false;
                                    }
                                }
                                else{
                                    direction_left = false;
                                }

                            }
                            else{
                                direction_left = false;
                            }
                        }
                        
                        if(direction_right){
                            dest_row = row;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_right = false;
                                    }
                                }
                                else{
                                    direction_right = false;
                                }

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
//TODO:
            case Piecetype::knight:
            {   
                if(board[row][column]->color == this->color_to_move){
                    for(int i = 1; i >= -1; i -= 2){//left/right
                        for(int j = 1; j <= 2; j++){//1 or 2 left/right
                            for(int k = 1; k >= -1; k -= 2){ //up/down
                                int dest_row = row - i*j;
                                int dest_column = column + k*(3-j);
                                if(valid_coordinates(dest_row, dest_column)){
                                    if(is_valid_dest_square(dest_row, dest_column, color_to_move)){
                                        possibleSquares.push_back(Square(dest_row, dest_column));
                                    }
                                }
                            }
                        }
                    }
                }
                
            }break;
                
            case Piecetype::bishop:
            {
                if(board[row][column]->color == this->color_to_move){
                    bool direction_top_left = true;
                    bool direction_top_right = true;
                    bool direction_bottom_left = true;
                    bool direction_bottom_right = true;
                    for(int offset = 1; offset <= 7; offset++){
                        int dest_row;
                        int dest_column; 
                        if(direction_top_left){
                            dest_row = row+offset;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top_left = false;
                                    }
                                }
                                else{
                                    direction_top_left = false;
                                }

                            }
                            else{
                                direction_top_left = false;
                            }
                        }

                        if(direction_top_right){
                           dest_row = row+offset;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_top_right = false;
                                    }
                                }
                                else{
                                    direction_top_right = false;
                                }

                            }
                            else{
                                direction_top_right = false;
                            }
                        }

                        if(direction_bottom_left){
                          dest_row = row-offset;
                            dest_column = column-offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom_left = false;
                                    }
                                }
                                else{
                                    direction_bottom_left = false;
                                }

                            }
                            else{
                                direction_bottom_left = false;
                            }  
                        }

                        if(direction_bottom_right){
                            dest_row = row-offset;
                            dest_column = column+offset;
                            if(valid_coordinates(dest_row, dest_column)){
                                if(is_valid_dest_square(dest_row,dest_column,color_to_move)){
                                    possibleSquares.push_back(Square(dest_row,dest_column));
                                    if(board[dest_row][dest_column]->type != Piecetype::none){
                                        direction_bottom_right = false;
                                    }
                                }
                                else{
                                    direction_bottom_right = false;
                                }

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

            //TODO:
            // - en passsant
            case Piecetype::pawn:
            {
                if(board[row][column]->color == color_to_move){
                    if(this->color_to_move == Color::white){
                        if(valid_coordinates(row+1, column)){
                            if(board[row+1][column]->type == Piecetype::none){
                                possibleSquares.push_back(Square(row+1,column));
                            }
                        }        
                        
                        if(row == 1 && valid_coordinates(row+2, column)){
                            if(board[row+1][column]->type == Piecetype::none){
                                if(board[row+2][column]->type == Piecetype::none){
                                    possibleSquares.push_back(Square(row+2,column));
                                }
                            }  
                        }   

                        if(valid_coordinates(row+1, column+1)){
                            if(board[row+1][column+1]->type != Piecetype::none && board[row+1][column+1]->color != color_to_move){
                                possibleSquares.push_back(Square(row+1,column+1));
                            }
                        }  

                        if(valid_coordinates(row+1, column-1)){
                            if(board[row+1][column-1]->type != Piecetype::none && board[row+1][column-1]->color != color_to_move){
                                possibleSquares.push_back(Square(row+1,column-1));
                            }
                        }  
                    }
                    else{
                        if(valid_coordinates(row-1, column)){
                            if(board[row-1][column]->type == Piecetype::none){
                                possibleSquares.push_back(Square(row-1,column));
                            }
                        }        
                        
                        if(row == 6 && valid_coordinates(row-2, column)){
                            if(board[row-1][column]->type == Piecetype::none){
                                if(board[row-2][column]->type == Piecetype::none){
                                    possibleSquares.push_back(Square(row-2,column));
                                }
                            }  
                        }   

                        if(valid_coordinates(row-1, column+1)){
                            if(board[row-1][column+1]->type != Piecetype::none && board[row-1][column+1]->color != color_to_move){
                                possibleSquares.push_back(Square(row-1,column+1));
                            }
                        }  

                        if(valid_coordinates(row-1, column-1)){
                            if(board[row-1][column-1]->type != Piecetype::none && board[row-1][column-1]->color != color_to_move){
                                possibleSquares.push_back(Square(row-1,column-1));
                            }
                        } 
                    }
                }

            }break;

            
            
            
            
           
            //TODO:
            // - castle
            case Piecetype::king:
            {
                if(board[row][column]->color == this->color_to_move){
                    if(valid_coordinates(row-1,column-1)){
                        if(is_valid_dest_square(row-1,column-1,color_to_move)){
                            possibleSquares.push_back(Square(row-1,column-1));
                        }
                    }
                    if(valid_coordinates(row+1,column-1)){
                        if(is_valid_dest_square(row+1,column-1,color_to_move)){
                            possibleSquares.push_back(Square(row+1,column-1));
                        }
                    }

                    if(valid_coordinates(row-1,column+1)){
                        if(is_valid_dest_square(row-1,column+1,color_to_move)){
                            possibleSquares.push_back(Square(row-1,column+1));
                        }
                    }
                    if(valid_coordinates(row+1,column+1)){
                        if(is_valid_dest_square(row+1,column+1,color_to_move)){
                            possibleSquares.push_back(Square(row+1,column+1));
                        }
                    }
                    
                    if(valid_coordinates(row-1,column)){
                        if(is_valid_dest_square(row-1,column,color_to_move)){
                            possibleSquares.push_back(Square(row-1,column));
                        }
                    }
                    if(valid_coordinates(row+1,column)){
                        if(is_valid_dest_square(row+1,column,color_to_move)){
                            possibleSquares.push_back(Square(row+1,column));
                        }
                    }

                    if(valid_coordinates(row,column-1)){
                        if(is_valid_dest_square(row,column-1,color_to_move)){
                            possibleSquares.push_back(Square(row,column-1));
                        }
                    }
                    if(valid_coordinates(row,column+1)){
                        if(is_valid_dest_square(row,column+1,color_to_move)){
                            possibleSquares.push_back(Square(row,column+1));
                        }
                    }
                    if(color_to_move == Color::white){
                        if(ply_white_king_moved == -1){
                            if(ply_white_a_rook_moved == -1){
                                if(!is_square_attacked(Square(0,4),Color::white)){
                                    if(board[0][3]->type == Piecetype::none && !is_square_attacked(Square(0,3), Color::white)){
                                        if(board[0][2]->type == Piecetype::none && board[0][1]->type == Piecetype::none){
                                            possibleSquares.push_back(Square(0,2)); // no need to check if c1 is in check because it gets tested on move gen
                                        }
                                    }
                                }
                            }
                            if(ply_white_h_rook_moved == -1){
                                if(!is_square_attacked(Square(0,4),Color::white)){
                                    if(board[0][5]->type == Piecetype::none && !is_square_attacked(Square(0,5), Color::white)){
                                        if(board[0][6]->type == Piecetype::none){
                                            possibleSquares.push_back(Square(0,6)); // no need to check if g1 is in check because it gets tested on move gen
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else{
                        if(ply_black_king_moved == -1){
                            if(ply_black_a_rook_moved == -1){
                                if(!is_square_attacked(Square(7,4),Color::black)){
                                    if(board[7][3]->type == Piecetype::none && !is_square_attacked(Square(7,3), Color::black)){
                                        if(board[7][2]->type == Piecetype::none && board[7][1]->type == Piecetype::none){
                                            possibleSquares.push_back(Square(7,2)); // no need to check if c8 is in check because it gets tested on move gen    
                                        }
                                    }
                                }
                            }
                            if(ply_black_h_rook_moved == -1){
                                if(!is_square_attacked(Square(7,4),Color::black)){
                                    if(board[7][5]->type == Piecetype::none && !is_square_attacked(Square(7,5), Color::black)){
                                        if(board[7][6]->type == Piecetype::none){
                                            possibleSquares.push_back(Square(7,6)); // no need to check if g8 is in check because it gets tested on move gen
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }break;

            default:
                break;
                
            }

            for (Square  s : possibleSquares){
                Move m = Move(Square(row, column), s, board[row][column]->color, board[row][column]->type, board[s.row][s.column]->type);

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