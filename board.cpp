#include "board.h"

Board::Board()
{
    clear();
}

void Board::clear()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(OneCell::CELL_EMPTY);
        }
    }
}

unsigned short int Board::get(unsigned short int y, unsigned short int x)
{
    return myBoard[y][x].get();
}
