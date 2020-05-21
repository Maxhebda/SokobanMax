#ifndef BOARD_H
#define BOARD_H
#include <onecell.h>

class Board
{
public:
    Board();
    void clear();
    void load();
    unsigned short int get(unsigned short int y, unsigned short int x);
    void set(unsigned short int y, unsigned short int x,unsigned short int a);
    unsigned short int pos_Steve_x;
    unsigned short int pos_Steve_y;
private:
    OneCell myBoard[13][15];                            // y=13 x=15
};

#endif // BOARD_H
