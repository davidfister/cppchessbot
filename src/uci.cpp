#include "board.hpp"
#include "engine.hpp"
#include <iostream>
#include <chrono>
#include <sstream>    

int uci(int depth){
    Board board = Board();
    board.init();
    Engine engine = Engine();
    engine.init(&board);  

    std::string uci_input;
    
    while (getline(std::cin, uci_input)) {
        if(uci_input == "uci") {
            std::cout << "id name cppchessbot"<<std::endl;
            std::cout << "id author davidfister"<<std::endl;
            std::cout << "uciok" <<std::endl;
        }
        else if(uci_input == "isready"){
            std::cout << "readyok" <<std::endl;
            //std::cout << "bestmove a1a2" <<std::endl; //resign
        }
        else if(uci_input == "quit"){
            return 0;
        }
        else if(uci_input.substr(0,8) == "position"){
            if(uci_input.substr(9,8) == "startpos"){
                if(uci_input.size() >22 && uci_input.substr(18,5) == "moves"){
                    if(uci_input.substr(uci_input.size() - 1) == "q"){
                        board.do_uci_move(uci_input.substr(uci_input.size() - 5,4));

                    }
                    else{
                        board.do_uci_move(uci_input.substr(uci_input.size() - 4));
                    }
                }
            }
        }
        else if (uci_input.substr(0, 2) == "go") {
            Move m = engine.find_best_move_minimax(depth);
            std::cout << "bestmove " <<  m.to_string() << std::endl;
            board.do_move(m);

        }

    
    }

    return 0;
}
