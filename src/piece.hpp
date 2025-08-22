//class for representing the pieces
#include <cstdint>

class Piece{
public:
    char type;
    uint8_t pos;
    bool set_pos(uint8_t x, uint8_t y);
    bool set_type(char type);
};