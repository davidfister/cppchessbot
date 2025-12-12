#include "benchmark.hpp"
#include <iostream>

//unused atp
template<typename T>
std::chrono::milliseconds time_function(T f, long count)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        f();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_do_move(long count){
    Board b{};
    b.init();
    Move m(b.board[1][0]->square,b.board[3][0]->square, b.board[1][0]->color,b.board[1][0]->type,b.board[3][0]->type);
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.do_move(m);
        b.undo_move(m);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_do_nullmove(long count){
    Board b{};
    b.init();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.do_nullmove();
        b.undo_nullmove();
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_is_draw(long count){
    Board b{};
    b.init();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_draw();
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_is_checkmate(long count){
    Board b{};
    b.init();
    
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_checkmate();
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_is_square_attacked(long count){
    Board b{};
    b.init();
    Square s = Square(4,5);
    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_square_attacked(s,Color::white);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_allMoves_withExistingList(long count){
    Board b{};
    b.init();
    Square s = Square(4,5);
    std::list<Move>* moves = new std::list<Move>;

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        moves->clear();
        b.allMoves(moves);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}
std::chrono::milliseconds time_allMoves_withoutExistingList(long count){
    Board b{};
    b.init();
    Square s = Square(4,5);

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        std::list<Move>* moves = new std::list<Move>;
        b.allMoves(moves);
        delete moves;
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_valid_coordinates(long count){
    Board b{};
    b.init();
    Square s = Square(4,5);

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.valid_coordinates(4,4);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_is_valid_dest_square(long count){
    Board b{};
    b.init();
    Square s = Square(4,5);

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_valid_dest_square(s.row,s.column,Color::white);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}


std::chrono::milliseconds time_is_legal_move(long count){
    Board b{};
    b.init();
    Move m(b.board[1][0]->square,b.board[3][0]->square, b.board[1][0]->color,b.board[1][0]->type,b.board[3][0]->type);

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_legal_move(m);
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}

std::chrono::milliseconds time_is_legal_nullmove(long count){
    Board b{};
    b.init();

    auto t1 = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < count; i++){
        b.is_legal_nullmove();
    }
    auto t2 = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::milliseconds> (t2-t1);
}




void benchmark(long count)
{

    Board b{};
    b.init();
    Engine e{};
    e.init(&b);
    e.find_best_move_minimax(4);


    long benchmark_calls_allMoves = b.benchmark_calls_allMoves;
    long benchmark_calls_do_move = b.benchmark_calls_do_move;
    long benchmark_calls_do_nullmove = b.benchmark_calls_do_nullmove;
    long benchmark_calls_undo_move = b.benchmark_calls_undo_move;
    long benchmark_calls_undo_nullmove = b.benchmark_calls_undo_nullmove;
    long benchmark_calls_is_checkmate = b.benchmark_calls_is_checkmate;
    long benchmark_calls_is_draw = b.benchmark_calls_is_draw;
    long benchmark_calls_is_square_attacked = b.benchmark_calls_is_square_attacked;
    long benchmark_calls_valid_coordinates = b.benchmark_calls_valid_coordinates;
    long benchmark_calls_is_valid_dest_square = b.benchmark_calls_is_valid_dest_square;
    long benchmark_calls_valid_is_legal_move = b.benchmark_calls_is_legal_move;
    long benchmark_calls_valid_is_legal_nullmove = b.benchmark_calls_is_legal_nullmove;

    std::cout << "DoUndoMove " << count << " times: " << time_do_move(count).count()<<std::endl;
    std::cout << "DoUndoNullMove " << count << " times: " << time_do_nullmove(count).count()<<std::endl;
    std::cout << "is_draw " << count << " times: " << time_is_draw(count).count()<<std::endl;
    std::cout << "is_checkmate " << count << " times: " << time_is_checkmate(count).count()<<std::endl;
    std::cout << "is_square_attacked " << count << " times: " << time_is_square_attacked(count).count()<<std::endl;
    std::cout << "allMoves without new/delete " << count << " times: " << time_allMoves_withExistingList(count).count()<<std::endl;
    std::cout << "allMoves with new/delete " << count << " times: " << time_allMoves_withExistingList(count).count()<<std::endl;
    std::cout << "Valid_coordinates " << count << " times: " << time_valid_coordinates(count).count()<<std::endl;
    std::cout << "is_valid_dest_square " << count << " times: " << time_is_valid_dest_square(count).count()<<std::endl;
    std::cout << "is_legal_move " << count << " times: " << time_is_legal_move(count).count()<<std::endl;
    std::cout << "is_legal_nullmove " << count << " times: " << time_is_legal_nullmove(count).count()<<std::endl;
    std::cout <<"---"<<std::endl;
    std::cout << "DoUndoMove " << benchmark_calls_do_move+benchmark_calls_undo_move << " times: " << time_do_move(benchmark_calls_do_move+benchmark_calls_undo_move).count()<<std::endl;
    std::cout << "DoUndoNullMove " << benchmark_calls_do_nullmove+benchmark_calls_undo_nullmove << " times: " << time_do_nullmove(benchmark_calls_do_nullmove+benchmark_calls_undo_nullmove).count()<<std::endl;
    std::cout << "is_draw " << benchmark_calls_is_draw << " times: " << time_is_draw(benchmark_calls_is_draw).count()<<std::endl;
    std::cout << "is_checkmate " << benchmark_calls_is_checkmate << " times: " << time_is_checkmate(benchmark_calls_is_checkmate).count()<<std::endl;
    std::cout << "is_square_attacked " << benchmark_calls_is_square_attacked << " times: " << time_is_square_attacked(benchmark_calls_is_square_attacked).count()<<std::endl;
    std::cout << "allMoves without new/delete " << benchmark_calls_allMoves << " times: " << time_allMoves_withExistingList(benchmark_calls_allMoves).count()<<std::endl;
    std::cout << "allMoves with new/delete " << benchmark_calls_allMoves << " times: " << time_allMoves_withExistingList(benchmark_calls_allMoves).count()<<std::endl;
    std::cout << "Valid_coordinates " << benchmark_calls_valid_coordinates << " times: " << time_valid_coordinates(benchmark_calls_valid_coordinates).count()<<std::endl;
    std::cout << "is_valid_dest_square " << benchmark_calls_is_valid_dest_square << " times: " << time_is_valid_dest_square(benchmark_calls_is_valid_dest_square).count()<<std::endl;
    std::cout << "is_legal_move " << benchmark_calls_valid_is_legal_move << " times: " << time_is_legal_move(benchmark_calls_valid_is_legal_move).count()<<std::endl;
    std::cout << "is_legal_nullmove " << benchmark_calls_valid_is_legal_nullmove << " times: " << time_is_legal_nullmove(benchmark_calls_valid_is_legal_nullmove).count()<<std::endl;

}