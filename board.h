#ifndef BOARD_H
#define BOARD_H
#include <onecell.h>

class Board
{
public:
    Board();
    void clear();
    unsigned short int get(unsigned short int y, unsigned short int x);
private:
    OneCell myBoard[13][15];                            // y=13 x=15
};

#endif // BOARD_H
