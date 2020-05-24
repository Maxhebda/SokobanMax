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
void Board::load(unsigned short int * levelPointer)
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(levelPointer[15*y+x]);
            if (levelPointer[15*y+x]==OneCell::CELL_STEVE || levelPointer[15*y+x]==OneCell::CELL_STEVEinHOLE)
            {
                pos_Steve_x=x;
                pos_Steve_y=y;
            }
            if (levelPointer[15*y+x]==OneCell::CELL_ARROW_DOWN)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y+1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y+2;
            }
            if (levelPointer[15*y+x]==OneCell::CELL_ARROW_UP)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y-1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y-2;
            }
            if (levelPointer[15*y+x]==OneCell::CELL_ARROW_RIGHT)
            {
                pos_Teleport_x=x+1;
                pos_Teleport_y=y;
                pos_Teleport_x_next=x+2;
                pos_Teleport_y_next=y;
            }
            if (levelPointer[15*y+x]==OneCell::CELL_ARROW_LEFT)
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
    if (y>12 || y<0 || x<0 || x>14) return OneCell::CELL_WALL;
    return myBoard[y][x].get();
}

void Board::set(unsigned short y, unsigned short x, unsigned short a)
{
    myBoard[y][x].set(a);
    if (a==OneCell::CELL_STEVE || a==OneCell::CELL_STEVEinHOLE)
    {
        pos_Steve_x=x;
        pos_Steve_y=y;
    }
}

bool Board::isWin()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (myBoard[y][x].get()==OneCell::CELL_DIAMOND)
                return false;
        }
    }
    return true;
}
