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
        uci(6);
    } 
    else {
        if(strcmp(argv[1],"benchmark") == 0){
            std::cout << "hi" <<std::endl;
            benchmark_flamegraph(6,10);
        }
    }
    //debug(100, 6);
    //benchmark(1000000);
    //
    return 0;
}