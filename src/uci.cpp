#include "board.hpp"
#include "engine.hpp"
#include <iostream>
#include <chrono>
#include <sstream>    

int uci(){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  

    int engine_depth = 4; 
    for(int i = 0; i < 10; i++){

    }
    std::string uci_input;
    
    while (getline(std::cin, uci_input)) {
        if(uci_input == "uci") {
            std::cout << "id name cppchessbot"<<std::endl;
            std::cout << "id author davidfister"<<std::endl;
            std::cout << "uciok" <<std::endl;
        }
        else if(uci_input == "isready"){
            std::cout << "readyok" <<std::endl;

        }
        else if(uci_input == "quit"){
            return 0;
        }
        else if(uci_input.substr(0,8) == "position"){
            if(uci_input.substr(9,8) == "startpos"){
                if(uci_input.size() >22 && uci_input.substr(18,5) == "moves"){
                    board.do_move(Move(uci_input.substr(uci_input.size() - 4),board.color_to_move));
                }
            }
        }
        else if (uci_input.substr(0, 2) == "go") {
            if(board.is_checkmate()){
                return 0;
            }
            if(board.is_draw()){
                return 0;
            }
            
            Move m = engine.find_best_move_minimax(engine_depth);
            board.do_move(m);
            std::cout << "bestmove " <<  m.to_string() << std::endl;

        }

    
    }

    return 0;
}
