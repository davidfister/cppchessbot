#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstdint>

class Square
{
public:
    Square();
    Square(uint8_t x, uint8_t y);
    uint8_t pos_x;
    uint8_t pos_y;
};

#endif