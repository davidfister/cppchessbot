#include "engine.hpp"

#include <iostream>

bool Engine::init(Board *board)
{
    this->board = board;
    return true;
}


Move Engine::find_best_move_minimax(int depth)
{

    std::vector<Move> moves;
    board->allMoves(&moves);
    Move bestMove = moves.front();

    //std::cout<<board->print_board()<<std::endl;
    //std::cout<<board->get_fen()<<std::endl;



    double alpha = -150000;
    double beta = 150000;
    for(Move m : moves){
        board->do_move(m);
        double e;
        if(board->color_to_move == Color::black){
            e = minimax_min(depth-1, alpha, beta);
            if(e > alpha){
                alpha = e;
                bestMove = m;
            }  
        }
        else{
            e = minimax_max(depth-1, alpha, beta);
            if(e < beta){
                beta = e;
                bestMove = m;
            }
        }

        board->undo_move(m);
    }

    return bestMove;
}

double Engine::minimax_max(int depth,double alpha, double beta)
{

    if(board->is_checkmate() == true || board->is_draw() == true || depth == 0){
        return this->evaluate_minimax(depth);
    }

    std::vector<Move> moves;
    board->allMoves(&moves);
    for (Move m : moves){
        board->do_move(m);
        
        double eval = minimax_min(depth-1, alpha, beta);
        
        /*if(m.is_capture && depth == 1){
            eval = minimax_min(1, alpha, beta);
        }
        else{
            eval = minimax_min(depth-1, alpha, beta);
        }*/
        
        if(beta < eval){

            board->undo_move(m);
            return beta;
        }
        if(eval > alpha){
            alpha = eval;
        }

        board->undo_move(m);
    }


    return alpha;
}

double Engine::minimax_min(int depth,double alpha, double beta)
{

    if(board->is_checkmate() == true || board->is_draw() == true ||  depth == 0){
        return this->evaluate_minimax(depth);
    }

    std::vector<Move> moves;
     board->allMoves(&moves);
    for (Move m : moves){
        board->do_move(m);
        
        double eval = minimax_max(depth-1, alpha, beta);
        
        /*if(m.is_capture && depth == 1){
            eval = minimax_max(1, alpha, beta);
        }
        else{
            eval = minimax_max(depth-1, alpha, beta);
        }*/
        
        if(alpha > eval){

            board->undo_move(m);
            return alpha;
        }
        if(eval < beta){
            beta = eval;
        }

        board->undo_move(m);
    }

    return beta;
}


int Engine::evaluate_minimax(int depth)
{
    if(board->is_draw()){
        return 0;
    }
    if(board->is_checkmate()){
        return board->color_to_move == Color::white ? -90000 - depth : 90000 + depth;
    }
    
    double evaluation = 0;
   
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            Piece* p = board->board[row][column];
            switch (p->type)
            {

            case Piecetype::pawn:
            {
                evaluation += p->color == Color::white ? 100 : -100 ;
                break;
            }
            case Piecetype::knight:
            {
                evaluation += p->color == Color::white ? 300 : -300;
                break;
            }
            case Piecetype::bishop:
            {
                evaluation += p->color == Color::white ? 300 : -300;
                break;
            }
            case Piecetype::rook:
            {
                evaluation += p->color == Color::white ? 500 : -500;
                break;
            }
            case Piecetype::queen:
            {
                evaluation += p->color == Color::white ? 900 : -900;
                break;
            }
            default:
                break;      
            }
            int i = 1;
            if(p->type == Piecetype::king){
                i = -1;
            }
            if(p->color == Color::white){
                 evaluation += row*10 * i;
            }
            else if(p->color == Color::black){
                evaluation -= (7-row)*10 * i;
            }
        }
    }

    if(board->is_white_castled){
        evaluation += 50;
    }
    if(board->is_black_castled){
        evaluation -= 50;
    }
    return evaluation;
}