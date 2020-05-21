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
void Board::load()
{
    const unsigned short int tmp[13*15]=
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0,
        0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,21, 5, 0, 0,
        0, 0, 5, 0, 0, 0, 2, 0,10, 5, 5, 0, 5, 0, 0,
        0, 0, 5, 5, 0, 5, 5, 5, 5, 5, 5, 0, 5, 0, 0,
        0, 0, 0, 5, 0, 5, 5, 0, 0, 0, 5, 0, 5, 0, 0,
        0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0,
        0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0,
        0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 5, 3, 5, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(tmp[15*y+x]);
        }
    }
}

unsigned short int Board::get(unsigned short int y, unsigned short int x)
{
    return myBoard[y][x].get();
}
