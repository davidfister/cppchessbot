#include "square.hpp"

Square::Square()
{
}

Square::Square(int row, int column)
{
    this->row = row;
    this->column = column;
}

bool Square::operator==(Square &s)
{
    if(this->column == s.column && this->row == s.row){
        return true;
    }
    else{
        return false;
    }
}
