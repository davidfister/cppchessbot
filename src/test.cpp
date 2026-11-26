#include "catch2/catch_amalgamated.hpp"

#include <cstdint>
#include "board.hpp"
#include "engine.hpp"
#include <math.h>

TEST_CASE( "Test bitboard on r2qk2r/pp1b1ppp/2n1pn2/2b1N3/2Np4/6P1/PP2PPBP/R1BQ1RK1 w kq - 1 10" ) {
    Board board = Board();
    std::vector<Move> * allMovesList = new std::vector<Move>;
    board.init("r2qk2r/pp1b1ppp/2n1pn2/2b1N3/2Np4/6P1/PP2PPBP/R1BQ1RK1 w kq - 1 10");
    REQUIRE( board.get_bitboard(0,0) == true);
    REQUIRE( board.get_bitboard(0,1) == false);
    REQUIRE( board.get_bitboard(7,7) == true);
}

TEST_CASE( "Test bitboard on standard init" ) {
    Board board = Board();
    std::vector<Move> * allMovesList = new std::vector<Move>;
    board.init();

    REQUIRE( board.get_bitboard(0,0) == true);
    REQUIRE( board.get_bitboard(0,1) == true);
    REQUIRE( board.get_bitboard(1,7) == true);

    REQUIRE( board.get_bitboard(2,2) == false);
    REQUIRE( board.get_bitboard(3,5) == false);
    REQUIRE( board.get_bitboard(5,2) == false);

    REQUIRE( board.get_bitboard(6,2) == true);
    REQUIRE( board.get_bitboard(7,6) == true);
    REQUIRE( board.get_bitboard(7,7) == true);
}

TEST_CASE( "Test en passant from uci" ) {
    Board board = Board();
    std::vector<Move> * allMovesList = new std::vector<Move>;
    board.init();
    board.do_uci_move("e2e4");
    board.do_uci_move("a7a6");
    board.do_uci_move("e4e5");
    board.do_uci_move("d7d5");
    board.do_uci_move("e5d4");


    REQUIRE(board.get_bitboard(3,4) == false);
    REQUIRE(board.get_bitboard(5,3) == false);
    REQUIRE(board.get_bitboard(4,3) == true);
    REQUIRE(board.get_bitboard(3,3) == false);


}

TEST_CASE( "Simpe undo move" ) {
    Board board = Board();
    std::vector<Move> * allMovesList = new std::vector<Move>;
    board.init();
    Move m = Move(Square(1,1), Square(2,1), Color::white, Piecetype::pawn, Piecetype::none);
    board.do_move(m);
    board.undo_move(m);

    board.print_bitboard();

    REQUIRE(board.get_bitboard(3,3) == false);
    REQUIRE(board.get_bitboard(1,1) == true);
    REQUIRE(board.get_bitboard(2,1) == false);

}


TEST_CASE( "Evals" ) {
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);
    
    REQUIRE(engine.evaluate_minimax(3) == 0);
    Move m = Move(Square(1,1), Square(3,1), Color::white, Piecetype::pawn, Piecetype::none);
    board.do_move(m);
    REQUIRE(round(10*engine.evaluate_minimax(3)) == round(10*0.2));
    m = Move(Square(6,1), Square(5,1), Color::white, Piecetype::pawn, Piecetype::none);
    board.do_move(m);
    REQUIRE(round(10*engine.evaluate_minimax(3)) == round(10*0.1));
    m = Move(Square(3,1), Square(4,1), Color::white, Piecetype::pawn, Piecetype::none);
    board.do_move(m);
    REQUIRE(round(10*engine.evaluate_minimax(3)) == round(10*0.2));
    board.undo_move(m);
    REQUIRE(round(10*engine.evaluate_minimax(3)) == round(10*0.1));

}
