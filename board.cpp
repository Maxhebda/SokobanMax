#include "board.h"

Board::Board()
{
    pos_Steve_x=-1;//null
    pos_Steve_y=-1;
    pos_arrow_x=-1;//null
    pos_arrow_y=-1;
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

void Board::clearToWall()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(OneCell::CELL_WALL);
        }
    }
}

void Board::load(QVector<unsigned short int> level)
{
    pos_Teleport_x=-1;
    pos_Teleport_y=-1;
    pos_Teleport_x_next=-1;
    pos_Teleport_y_next=-1;
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            myBoard[y][x].set(level[15*y+x]);
            if (level[15*y+x]==OneCell::CELL_STEVE || level[15*y+x]==OneCell::CELL_STEVEinHOLE)
            {
                pos_Steve_x=x;
                pos_Steve_y=y;
            }
            if (level[15*y+x]==OneCell::CELL_ARROW_DOWN)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y+1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y+2;
            }
            if (level[15*y+x]==OneCell::CELL_ARROW_UP)
            {
                pos_Teleport_x=x;
                pos_Teleport_y=y-1;
                pos_Teleport_x_next=x;
                pos_Teleport_y_next=y-2;
            }
            if (level[15*y+x]==OneCell::CELL_ARROW_RIGHT)
            {
                pos_Teleport_x=x+1;
                pos_Teleport_y=y;
                pos_Teleport_x_next=x+2;
                pos_Teleport_y_next=y;
            }
            if (level[15*y+x]==OneCell::CELL_ARROW_LEFT)
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
    if (a==OneCell::CELL_STEVE || a==OneCell::CELL_STEVEinHOLE)
    {
        pos_Steve_x=x;
        pos_Steve_y=y;
    }
    else
    if ((myBoard[y][x].get()==OneCell::CELL_STEVE || myBoard[y][x].get()==OneCell::CELL_STEVEinHOLE) && (a!=OneCell::CELL_STEVE || a!=OneCell::CELL_STEVEinHOLE))     //delete steve
    {
        pos_Steve_x=-1;
    }
    if (a==OneCell::CELL_ARROW_UP || a==OneCell::CELL_ARROW_DOWN || a==OneCell::CELL_ARROW_LEFT || a==OneCell::CELL_ARROW_RIGHT)
    {
        pos_arrow_x=x;
        pos_arrow_y=y;
    }
    else
    if ((myBoard[y][x].get()==OneCell::CELL_ARROW_UP || myBoard[y][x].get()==OneCell::CELL_ARROW_DOWN || myBoard[y][x].get()==OneCell::CELL_ARROW_LEFT || myBoard[y][x].get()==OneCell::CELL_ARROW_RIGHT) && a!=OneCell::CELL_ARROW_UP && a!=OneCell::CELL_ARROW_DOWN && a!=OneCell::CELL_ARROW_LEFT && a!=OneCell::CELL_ARROW_RIGHT)
    {
        pos_arrow_x=-1;
    }
    myBoard[y][x].set(a);
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
