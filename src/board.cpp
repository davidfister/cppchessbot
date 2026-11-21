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

bool Board::is_valid_dest_square(int row, int column, Color color_of_moving_piece)
{    
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
    
    Piece* currentKing = this->color_to_move == Color::white ? whiteKing : blackKing;

    this->do_nullmove();
    bool a = is_square_attacked(currentKing->square, currentKing->color);   
    this->undo_nullmove();
    return !a;
}

bool Board::is_square_attacked(Square s, Color attackedColor)
{   
    if (attacked_squares[s.row][s.column]){
        return true;
    }
    
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
    
    if(is_legal_nullmove()){
        return false;
    }
    
    std::vector<Move>* moves = NULL;

    if(this->allMoves(moves)->size() != 0){
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
    return true;
}

bool Board::is_draw()
{    
    std::vector<Move>* moves = NULL;

    if(this->allMoves(moves)->size() != 0){
        return false;
    }
    return is_legal_nullmove();
}

void Board::init()
{   
    init("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::init(std::string s)
{
    captureStack.reserve(32);
    
    std::string substring;
    std::vector<std::string> substrings;
    std::string row_string;
    std::vector<std::string> row_strings;
    size_t pos = 0;
    
    while ((pos = s.find(' ')) != std::string::npos){
        substring = s.substr(0, pos);
        substrings.push_back(substring);
        s.erase(0, pos + 1);
        
    }
    substrings.push_back(s);

    
    std::string board_string = substrings[0];

    while ((pos = board_string.find("/")) != std::string::npos) {
        row_string = board_string.substr(0, pos);

        row_strings.push_back(row_string);
        board_string.erase(0, pos + 1);
    }
    row_strings.push_back(board_string);
    
    int row = 7;
    int col = 0;
    Color color;
    for(auto r : row_strings){
        for (auto &c: r){
            if(c >= '0' && c <= '8'){
                for (int i = 0; i < (int) c - '0'; i++){
                    board[row][col] = new Piece(Color::clear, Piecetype::none, Square(row,col));
                    col++;

                }
                
            }
            else if(c == 'K' || c == 'k'){
                color = (c == 'K') ? Color::white : Color::black;
                board[row][col] = new Piece(color, Piecetype::king, Square(row,col));
                if(color == Color::white){
                    whiteKing = board[row][col];
                }
                else{
                    blackKing = board[row][col];
                }
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;


            }

            else if(c == 'R' || c == 'r'){
                color = (c == 'R') ? Color::white : Color::black;
                board[row][col] = new Piece(color, Piecetype::rook, Square(row,col));
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;
            }

            else if(c == 'N' || c == 'n'){
                color = (c == 'N') ? Color::white : Color::black;
                board[row][col] = new Piece(color, Piecetype::knight, Square(row,col));
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;
            }

            else if(c == 'B' || c == 'b'){
                color = (c == 'B') ? Color::white : Color::black;
                board[row][col] = new Piece(color, Piecetype::bishop, Square(row,col));
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;
            }

            else if(c == 'Q' || c == 'q'){
                color = (c == 'Q') ? Color::white : Color::black; 
                board[row][col] = new Piece(color, Piecetype::queen, Square(row,col));
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;
            }
            else if(c == 'P' || c == 'p'){
                color = (c == 'P') ? Color::white : Color::black;
                board[row][col] = new Piece(color, Piecetype::pawn, Square(row,col));
                blankPieceStack.push_back(new Piece(Color::clear, Piecetype::none ,Square(row,col)));
                col++;
            }
            else{
                std::cout << "Invalid token in input fen string"<<std::endl;
                exit(-1);
            }
        }    
        row -= 1;
        col = 0;
    }
    

    std::string color_to_move_string = substrings[1];
    if(color_to_move_string == "w"){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }
    
    /*std::string ply_string = substrings[5];
    if (this->color_to_move == Color::white){
        this->ply = std::stoi(ply_string)*2-1;
    }
    else{
        this->ply = std::stoi(ply_string)*2;
    }*/
    this->ply = 1;
    std::string castle_string = substrings[2];
    this->ply_white_h_rook_moved = ply;
    this->ply_black_h_rook_moved = ply;
    this->ply_white_a_rook_moved = ply;
    this->ply_black_a_rook_moved = ply;



    if(castle_string != "-"){
        for(auto& c : castle_string){
            switch (c)
            {
            case 'K':
                this->ply_white_h_rook_moved = -1;
                break;
            case 'k':
                this->ply_black_h_rook_moved = -1;
                break;

            case 'Q':
                this->ply_white_a_rook_moved = -1;
                break;
            case 'q':
                this->ply_black_a_rook_moved = -1;
                break;
            default:
                break;
            }
        }
    }
    
    std::string en_passant_string = substrings[3];
    if(en_passant_string == "-"){
        en_passant_squares.push_back(Square(-10,-10)); //TODO why?
    }
    else{
        Square eps = Square(-((int)'1' - en_passant_string.at(1)),-((int)'a' - en_passant_string.at(0)));

        en_passant_squares.push_back(eps);
    }

    

}

std::string Board::print_board()
{
    std::string board_string = "";
    
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            char offset = 0;
            if(board[i][j]->color == Color::white){
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

std::string Board::get_fen(){
    std::string fen_string = "";
    int empty_counter = 0;
    char offset = 0;
    fen_string.reserve(128);
    
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            offset = 0;
            if(board[i][j]->color == Color::white){
                offset = ('a' - 'A');
            }
            if(empty_counter != 0 && board[i][j]->type != Piecetype::none){
                fen_string.push_back(empty_counter);
                empty_counter = 0;

            }
            switch(board[i][j]->type){
                case Piecetype::pawn:
                    fen_string.push_back('p' - offset);
                break;
                case Piecetype::knight:
                    fen_string.push_back('n' - offset);
                break;
                case Piecetype::bishop:
                    fen_string.push_back('b' - offset);
                break;
                case Piecetype::rook:
                    fen_string.push_back('r' - offset);
                break;
                case Piecetype::queen:
                    fen_string.push_back('q' - offset);
                break;
                case Piecetype::king:
                    fen_string.push_back('k' - offset);
                break;
                default:
                    empty_counter++;                    
                break;

            };   
        }
        if(empty_counter != 0){
            fen_string.push_back(empty_counter);
        }

        fen_string.push_back('/');
        empty_counter = 0;
    }
    fen_string.pop_back();
    
    fen_string.push_back(' ');
    if(this->color_to_move == Color::white){
        fen_string.push_back('w');
    }
    else{
        fen_string.push_back('b');
    }
    return fen_string;
}


bool Board::do_uci_move(std::string s)
{
    Square start_square = Square(-((int)'1' - s.at(1)),-((int)'a' - s.at(0)));
    Square end_square = Square(-((int)'1' - s.at(3)),-((int)'a' - s.at(2)));
    
    Move m = Move(start_square, end_square, color_to_move, board[start_square.row][start_square.column]->type, board[end_square.row][end_square.column]->type);
    this->do_move(m);
    return true;
}

bool Board::do_move(Move move)
{   
    this->n_do_move++;
    
    this->ply++;
    
    if(!move.is_en_passant){
        if (move.is_capture){
            this->captureStack.push_back(board[move.end_square.row][move.end_square.column]);
            board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
            board[move.start_square.row][move.start_square.column] = blankPieceStack.back();
            blankPieceStack.pop_back();
            board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
            board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;
        }
        else{
            Piece* t = board[move.end_square.row][move.end_square.column];
            board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
            
            board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
            board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
            
            board[move.start_square.row][move.start_square.column] = t;
            board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
            board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;
        }
    }
    else {
        //Switch start and end pos
        Piece* t = board[move.end_square.row][move.end_square.column];
        board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
        
        board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
        board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
        
        board[move.start_square.row][move.start_square.column] = t;
        board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
        board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;
        
        if(move.color_moved_piece == Color::white){ 
            this->captureStack.push_back(board[move.end_square.row-1][move.end_square.column]);
            board[move.end_square.row-1][move.end_square.column] = blankPieceStack.back();
            blankPieceStack.pop_back();
            board[move.end_square.row-1][move.end_square.column]->square.row = move.end_square.row-1;
            board[move.end_square.row-1][move.end_square.column]->square.column = move.end_square.column;
        }
        else{
            this->captureStack.push_back(board[move.end_square.row+1][move.end_square.column]);
            board[move.end_square.row+1][move.end_square.column] = blankPieceStack.back();
            blankPieceStack.pop_back();
            board[move.end_square.row+1][move.end_square.column]->square.row = move.end_square.row+1;
            board[move.end_square.row+1][move.end_square.column]->square.column = move.end_square.column;       
        }
    }


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
    
    if(move.moved_piece == Piecetype::pawn){
        if(abs(move.start_square.row-move.end_square.row)==2){
            en_passant_squares.push_back(Square(move.start_square.row+(move.end_square.row-move.start_square.row)/2, move.start_square.column));
        }
        else{
            en_passant_squares.push_back(Square(-10,-10));
        }
    }
    else{
        en_passant_squares.push_back(Square(-10,-10));
    }

    if(move.is_promotion){
        delete board[move.end_square.row][move.end_square.column];
        board[move.end_square.row][move.end_square.column] = new Piece(move.color_moved_piece, Piecetype::queen, Square(move.end_square.row, move.end_square.column));
    }

    

    if(move.is_castle){
        if(move.end_square.column == 6){
            Piece* r = board[move.end_square.row][7];
            board[move.end_square.row][7] = board[move.end_square.row][5];
            board[move.end_square.row][5] = r;
            if(move.color_moved_piece == Color::white){
                ply_white_h_rook_moved = ply;
                ply_white_king_moved = ply;
                is_white_castled = true;
            }
            else{
                ply_black_h_rook_moved = ply;
                ply_black_king_moved = ply;
                is_black_castled = true;
            }
        }
        else{
            Piece* r = board[move.end_square.row][0];
            board[move.end_square.row][0] = board[move.end_square.row][3];
            board[move.end_square.row][3] = r;
            if(move.color_moved_piece == Color::white){
                ply_white_a_rook_moved = ply;
                ply_white_king_moved = ply;
                is_white_castled = true;
            }
            else{
                ply_black_a_rook_moved = ply;
                ply_black_king_moved = ply;
                is_black_castled = true;
            }
        }
        
        
    }

    board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
    board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
    
    
    
    return true;
}

bool Board::do_nullmove()
{
    this->ply++;
    
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
    this->n_undo_move++;
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }
    if(!move.is_en_passant){
        if(move.is_capture){
            this->blankPieceStack.push_back(board[move.start_square.row][move.start_square.column]);
            board[move.start_square.row][move.start_square.column] = board[move.end_square.row][move.end_square.column];
            board[move.end_square.row][move.end_square.column] = this->captureStack.back();
            this->captureStack.pop_back();
        }
        else{
            Piece* t = board[move.end_square.row][move.end_square.column];
            board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
            
            board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
            board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
            
            board[move.start_square.row][move.start_square.column] = t;
            board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
            board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;
        }    
    }
    else{
            //switch start and end
            Piece* t = board[move.end_square.row][move.end_square.column];
            board[move.end_square.row][move.end_square.column] = board[move.start_square.row][move.start_square.column];
            
            board[move.end_square.row][move.end_square.column]->square.row = move.end_square.row;
            board[move.end_square.row][move.end_square.column]->square.column = move.end_square.column;
            
            board[move.start_square.row][move.start_square.column] = t;
            board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
            board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;

            if(move.color_moved_piece == Color::white){ 
                this->blankPieceStack.push_back(board[move.end_square.row-1][move.end_square.column]);
                board[move.end_square.row-1][move.end_square.column] = this->captureStack.back();
                this->captureStack.pop_back();
            }
            else{ 
                this->blankPieceStack.push_back(board[move.end_square.row+1][move.end_square.column]);
                board[move.end_square.row+1][move.end_square.column] = this->captureStack.back();
                this->captureStack.pop_back();
            }
        
            
    }
    
    

    if(move.is_promotion){
        delete board[move.start_square.row][move.start_square.column];
        board[move.start_square.row][move.start_square.column] = new Piece(move.color_moved_piece, Piecetype::pawn, Square(move.start_square.row, move.start_square.column));
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

    en_passant_squares.pop_back();
    board[move.start_square.row][move.start_square.column]->square.row = move.start_square.row;
    board[move.start_square.row][move.start_square.column]->square.column = move.start_square.column;


    this->ply--;
    return true;
}

bool Board::undo_nullmove()
{
    
    if(this->color_to_move == Color::black){
        this->color_to_move = Color::white;
    }
    else{
        this->color_to_move = Color::black;
    }
    this->ply--;
    return true;
}

void Board::generate_possible_squares(int row, int column){



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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                        this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                        this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                        this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                        this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = dest_row;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = dest_column;
                                    this->possibleSquaresCounter += 1;
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
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                                this->possibleSquaresCounter += 1;
                            }
                        }        
                        
                        if(row == 1 && valid_coordinates(row+2, column)){
                            if(board[row+1][column]->type == Piecetype::none){
                                if(board[row+2][column]->type == Piecetype::none){
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+2;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                                    this->possibleSquaresCounter += 1;
                                }
                            }  
                        }   

                        if(valid_coordinates(row+1, column+1)){
                            if((board[row+1][column+1]->type != Piecetype::none && board[row+1][column+1]->color != color_to_move) || (en_passant_squares[ply-1].row == row+1 && en_passant_squares[ply-1].column == column +1)){
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column+1;
                                this->possibleSquaresCounter += 1;
                            }
                        }  

                        if(valid_coordinates(row+1, column-1)){
                            if((board[row+1][column-1]->type != Piecetype::none && board[row+1][column-1]->color != color_to_move) || (en_passant_squares[ply-1].row == row+1 && en_passant_squares[ply-1].column == column -1)){
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column-1;
                                this->possibleSquaresCounter += 1;
                            }
                        }  
                    }
                    else{
                        if(valid_coordinates(row-1, column)){
                            if(board[row-1][column]->type == Piecetype::none){
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                                this->possibleSquaresCounter += 1;
                            }
                        }        
                        
                        if(row == 6 && valid_coordinates(row-2, column)){
                            if(board[row-1][column]->type == Piecetype::none){
                                if(board[row-2][column]->type == Piecetype::none){
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-2;
                                    this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                                    this->possibleSquaresCounter += 1;
                                }
                            }  
                        }   

                        if(valid_coordinates(row-1, column+1)){
                            if((board[row-1][column+1]->type != Piecetype::none && board[row-1][column+1]->color != color_to_move)|| (en_passant_squares[ply].row == row-1 && en_passant_squares[ply].column == column +1)){
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column+1;
                                this->possibleSquaresCounter += 1;
                            }
                        }  

                        if(valid_coordinates(row-1, column-1)){
                            if((board[row-1][column-1]->type != Piecetype::none && board[row-1][column-1]->color != color_to_move) || (en_passant_squares[ply-1].row == row-1 && en_passant_squares[ply-1].column == column -1)){
                                this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column-1;
                                this->possibleSquaresCounter += 1;
                            }
                        } 
                    }
                }

            }break;

           
            //TODO:
            case Piecetype::king:
            {
                if(board[row][column]->color == this->color_to_move){
                    if(valid_coordinates(row-1,column-1)){
                        if(is_valid_dest_square(row-1,column-1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column-1;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    if(valid_coordinates(row+1,column-1)){
                        if(is_valid_dest_square(row+1,column-1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                                this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column-1;
                                this->possibleSquaresCounter += 1;
                        }
                    }

                    if(valid_coordinates(row-1,column+1)){
                        if(is_valid_dest_square(row-1,column+1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column+1;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    if(valid_coordinates(row+1,column+1)){
                        if(is_valid_dest_square(row+1,column+1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column+1;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    
                    if(valid_coordinates(row-1,column)){
                        if(is_valid_dest_square(row-1,column,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row-1;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    if(valid_coordinates(row+1,column)){
                        if(is_valid_dest_square(row+1,column,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row+1;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column;
                            this->possibleSquaresCounter += 1;
                        }
                    }

                    if(valid_coordinates(row,column-1)){
                        if(is_valid_dest_square(row,column-1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column-1;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    if(valid_coordinates(row,column+1)){
                        if(is_valid_dest_square(row,column+1,color_to_move)){
                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = row;
                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = column+1;
                            this->possibleSquaresCounter += 1;
                        }
                    }
                    if(color_to_move == Color::white){
                        if(ply_white_king_moved == -1){
                            if(ply_white_a_rook_moved == -1){
                                if(!is_square_attacked(Square(0,4),Color::white)){
                                    if(board[0][3]->type == Piecetype::none && !is_square_attacked(Square(0,3), Color::white)){
                                        if(board[0][2]->type == Piecetype::none && board[0][1]->type == Piecetype::none){
                                            // no need to check if c1 is in check because it gets tested on move gen
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = 0;
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = 2;
                                            this->possibleSquaresCounter += 1;
                                        }
                                    }
                                }
                            }
                            if(ply_white_h_rook_moved == -1){
                                if(!is_square_attacked(Square(0,4),Color::white)){
                                    if(board[0][5]->type == Piecetype::none && !is_square_attacked(Square(0,5), Color::white)){
                                        if(board[0][6]->type == Piecetype::none){
                                            // no need to check if g1 is in check because it gets tested on move gen
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = 0;
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = 6;
                                            this->possibleSquaresCounter += 1;
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
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = 7;
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = 2;
                                            this->possibleSquaresCounter += 1;
                                        }
                                    }
                                }
                            }
                            if(ply_black_h_rook_moved == -1){
                                if(!is_square_attacked(Square(7,4),Color::black)){
                                    if(board[7][5]->type == Piecetype::none && !is_square_attacked(Square(7,5), Color::black)){
                                        if(board[7][6]->type == Piecetype::none){
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2] = 7;
                                            this->possibleSquaresArray[this->possibleSquaresCounter*2+1] = 6;
                                            this->possibleSquaresCounter += 1;                                        }
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
}

std::vector<Move> *Board::allMoves(std::vector<Move> *allMovesList){
    std::string fen = this->get_fen();
    allmoves_fen_map[fen] += 1;
    
    if(allmoves_map.count(fen)!=0){
        allMovesList = allmoves_map[fen];
        return allMovesList;
    }
    
    allMovesList = new std::vector<Move>;
    allMovesList->reserve(32);
    
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++)
        {
            possibleSquaresCounter = 0;
            generate_possible_squares(row, column);

            for(int i = 0; i < possibleSquaresCounter;i++){
                Move m = Move(Square(row, column), Square(possibleSquaresArray[i*2], possibleSquaresArray[i*2+1]), board[row][column]->color, board[row][column]->type, board[possibleSquaresArray[i*2]][possibleSquaresArray[i*2+1]]->type);

                if(is_legal_move(m)){
                    if(m.is_capture == true){
                        allMovesList->insert(allMovesList->begin(),m);
                    }
                    else{
                        allMovesList->push_back(m);
                    }
                }
            }   
        }
    
    }
    //allmoves_map.insert({fen,allMovesList});
    return allMovesList;
}