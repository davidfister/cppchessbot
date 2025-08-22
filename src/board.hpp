//Start by generating a slow but working move generator. Initial idea is using array based representation of the board with classes for each piece. 
//After implementing i will probably switch to bitboards or some other board representation. 

#include"piece.hpp"
#include <string>

class Board
{
    Piece board[8][8]; //[1][0] = b1
public:
    void init();
    std::string print_board();
};