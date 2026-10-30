#include "board.hpp"
#include "engine.hpp"
#include "debug.hpp"
#include "uci.hpp"
#include "benchmark.hpp"
#include "benchmark_flamegraph.hpp"
#include <string.h>
#include <iostream>


int main(int argc, char *argv[]){
    
    if(argc == 1){
        uci(4);
    } 
    else {
        if(strcmp(argv[1],"benchmark") == 0){
            if(argc != 4){
                std::cout << "usage: ./engine.out benchmark depth moves" <<std::endl;
                return 0;
            }
            else{
                std::cout << "Started benchmark..." <<std::endl;
                benchmark_flamegraph(atoi(argv[2]), atoi(argv[3]));
            }
            
        }
    }
    //debug(100, 6);
    //benchmark(1000000);
    //
    return 0;
}