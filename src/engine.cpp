#include "engine.hpp"

#include <iostream>

bool Engine::init(Board *board)
{
    this->board = board;
    return true;
}



// Move Engine::find_best_move_negamax(int depth)
// {
//     std::list<Move> mvs = this->board->allMoves();

//     Move best_move = this->board->allMoves().front();
//     double best_eval = -1000;

//     for(Move m : mvs){
//         board->do_move(m);
//         double eval_m = negamax(depth, -1000,1000);
//         if(eval_m > best_eval){
//             best_move = m;
//         }
//         board->undo_move(m);
//     }

//     return best_move;
// }


// double Engine::negamax(int depth, double alpha, double beta)
// {
//     if(board->is_checkmate() == true || board->is_draw() == true || depth == 0){
//         return this->evaluate();
//     }

//     double eval = -1000;
//     std::list<Move>* moves = new std::list<Move>;

//     for (Move m : *board->allMoves(moves)){
//         board->do_move(m);
//         eval = std::max(eval, -negamax(depth-1,-beta, -alpha ));
//         alpha = std::max(alpha, eval);
//         if(alpha >= beta){
//             benchmark_cutoffs++;
//             board->undo_move(m);
//             break;
//         }
//         board->undo_move(m);
//     }
//     return eval;
// }

// double Engine::evaluate()
// {
//     if(board->is_draw()){
//         return 0.0;
//     }
//     if(board->is_checkmate()){
//         return -1000;
//     }
    
//     double evaluation = 0;
   
//     for(int row = 0; row < 8; row++){
//         for(int column = 0; column < 8; column++){
//             Piece* p = board->board[row][column];
//             switch (p->type)
//             {

//             case Piecetype::pawn:
//             {
//                 evaluation += p->color == Color::white ? 1 + p->square.row*0.1 : -1 - (7-p->square.row)*0.1;
//                 break;
//             }
//             case Piecetype::knight:
//             {
//                 evaluation += p->color == Color::white ? 3 : -3;
//                 break;
//             }
//             case Piecetype::bishop:
//             {
//                 evaluation += p->color == Color::white ? 3 : -3;
//                 break;
//             }
//             case Piecetype::rook:
//             {
//                 evaluation += p->color == Color::white ? 5 : -5;
//                 break;
//             }
//             case Piecetype::queen:
//             {
//                 evaluation += p->color == Color::white ? 9 : -9;
//                 break;
//             }
//             default:
//                 break;      
//             }
//         }
//     }

//     return (board->color_to_move == Color::black) ? -evaluation : evaluation;
// }


Move Engine::find_best_move_minimax(int depth)
{
    double eval = board->color_to_move == Color::white ? -10001 : 10001;
    
    std::list<Move>* moves = new std::list<Move>;
    Move bestMove = board->allMoves(moves)->front();

    double alpha = -1500;
    double beta = 1500;
    for(Move m : *moves){
        m.print_move();
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
        std::cout << e << std::endl;
        board->undo_move(m);

    }
    delete moves;
    return bestMove;
}

double Engine::minimax_max(int depth,double alpha, double beta)
{
    if(board->is_checkmate() == true || board->is_draw() == true || depth == 0){
        return this->evaluate_minimax(depth);
    }

    std::list<Move>* moves = new std::list<Move>;
    for (Move m : *board->allMoves(moves)){
        board->do_move(m);
        double eval = minimax_min(depth-1, alpha, beta);
        if(beta < eval){
            benchmark_cutoffs++;
            board->undo_move(m);
            delete moves;
            return eval;
        }
        if(eval > alpha){
            alpha = eval;
        }
        board->undo_move(m);
    }
    delete moves;
    return alpha;
}

double Engine::minimax_min(int depth,double alpha, double beta)
{
    if(board->is_checkmate() == true || board->is_draw() == true || depth == 0){
        return this->evaluate_minimax(depth);
    }

    std::list<Move>* moves = new std::list<Move>;
    for (Move m : *board->allMoves(moves)){
        board->do_move(m);
        
        double eval = minimax_max(depth-1, alpha, beta);
        if(alpha > eval){
           benchmark_cutoffs++;
           board->undo_move(m);
            delete moves;
            return alpha;
        }
        if(eval < beta){
            beta = eval;
        }

        board->undo_move(m);
    }
    delete moves;
    return beta;
}


double Engine::evaluate_minimax(int depth)
{
    if(board->is_draw()){
        return 0.0;
    }
    if(board->is_checkmate()){
        return board->color_to_move == Color::white ? -900 - depth : 900 + depth;
    }
    
    double evaluation = 0;
   
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            Piece* p = board->board[row][column];
            switch (p->type)
            {

            case Piecetype::pawn:
            {
                evaluation += p->color == Color::white ? 1.0 + row/10.0: -(1.0 + (7-row)/10.0) ;
                break;
            }
            case Piecetype::knight:
            {
                evaluation += p->color == Color::white ? 3.0 + row/8.0 : -(3.0 + (7-row)/8.0);
                break;
            }
            case Piecetype::bishop:
            {
                evaluation += p->color == Color::white ? 3.0 : -3.0;
                break;
            }
            case Piecetype::rook:
            {
                evaluation += p->color == Color::white ? 5.0 + row/15.0 : -(3.0 + (7-row)/15.0);
                break;
            }
            case Piecetype::queen:
            {
                evaluation += p->color == Color::white ? 9.0 : -9.0;
                break;
            }
            default:
                break;      
            }
        }
    }
    return evaluation;
}