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
//    const unsigned short int tmp[13*15]=
//    {
//        5, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 5,
//        0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0,
//        0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,21, 5, 0, 0,
//        0, 0, 5, 0, 0, 0, 2, 0,10, 5, 5, 0, 5, 0, 0,
//        0, 2, 5, 5, 0, 5, 5, 5, 5, 5, 5, 0, 5, 0, 0,
//        0, 0, 0, 5, 0, 5, 5, 0, 0, 0, 5, 0, 5, 0, 0,
//        0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0,
//        0, 2, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 0,
//        0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 5, 3, 5, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0,
//        0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
//        5,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5
//    };
    const unsigned short int tmp[13*15]=
    {
        5, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 5,
        0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0,
        0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0,21, 0, 0, 0,
       10, 0, 5, 0, 0, 0, 2, 0,10, 0, 0, 0, 0, 0, 0,
        0, 2, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
        0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,
        0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 3, 5, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
        5,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5
    };

    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(tmp[15*y+x]);
            if (tmp[15*y+x]==OneCell::CELL_STEVE)
            {
                pos_Steve_x=x;
                pos_Steve_y=y;
            }
            if (tmp[15*y+x]==OneCell::CELL_ARROW_DOWN)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y+1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y+2;
            }
            if (tmp[15*y+x]==OneCell::CELL_ARROW_UP)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y-1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y-2;
            }
            if (tmp[15*y+x]==OneCell::CELL_ARROW_RIGHT)
            {
                pos_Teleport_x=x+1;
                pos_Teleport_y=y;
                pos_Teleport_x_next=x+2;
                pos_Teleport_y_next=y;
            }
            if (tmp[15*y+x]==OneCell::CELL_ARROW_LEFT)
            {
                pos_Teleport_x=x-1;
                pos_Teleport_y=y;
                pos_Teleport_x_next=x-2;
                pos_Teleport_y_next=y;
            }
        }
    }
}

unsigned short int Board::get(unsigned short int y, unsigned short int x)
{
    return myBoard[y][x].get();
}

void Board::set(unsigned short y, unsigned short x, unsigned short a)
{
    myBoard[y][x].set(a);
    if (a==OneCell::CELL_STEVE)
    {
        pos_Steve_x=x;
        pos_Steve_y=y;
    }
}
