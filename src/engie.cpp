#include "engie.hpp"

bool Engine::init(Board *board)
{
    this->board = board;
    return true;
}



Move Engine::find_best_move()
{
    std::list<Move> mvs = this->board->allMoves();

    Move best_move = this->board->allMoves().front();
    double best_eval = -1000;

    for(Move m : mvs){
        board->do_move(m);
        double eval_m = negamax(2, -1000,1000);
        if(eval_m > best_eval){
            best_move = m;
        }
        board->undo_move(m);
    }

    return best_move;
}

double Engine::negamax(int depth, double alpha, double beta)
{
    if(board->is_checkmate() == true || board->is_draw() == true || depth == 0){
        return this->evaluate();
    }

    double eval = -1000;

    for (Move m : board->allMoves()){
        board->do_move(m);
        eval = std::max(eval, -negamax(depth-1, -beta, -alpha));
        if(alpha >= beta){
            break;
        }
        board->undo_move(m);
    }
    return eval;
}

double Engine::evaluate()
{
    if(board->is_draw()){
        return 0.0;
    }
    if(board->is_checkmate()){
        return -1000;
    }
    
    double evaluation = 0;
   
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            Piece* p = board->board[row][column];
            switch (p->type)
            {

            case Piecetype::pawn:
            {
                evaluation += p->color == Color::white ? 1 + p->square.row*0.1 : -1;
                break;
            }
            case Piecetype::knight:
            {
                evaluation += p->color == Color::white ? 3 : -3;
                break;
            }
            case Piecetype::bishop:
            {
                evaluation += p->color == Color::white ? 3 : -3;
                break;
            }
            case Piecetype::rook:
            {
                evaluation += p->color == Color::white ? 5 : -5;
                break;
            }
            case Piecetype::queen:
            {
                evaluation += p->color == Color::white ? 9 : -9;
                break;
            }
            default:
                break;      
            }
        }
    }
    return (board->color_to_move == Color::black) ? -evaluation : evaluation;
}