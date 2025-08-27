#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstdint>

class Square
{
public:
    Square();
    Square(int row, int column);
    int row;
    int column;
};

#endif