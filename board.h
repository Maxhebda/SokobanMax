#ifndef BOARD_H
#define BOARD_H
#include <onecell.h>
#include <QVector>

class Board
{
public:
    Board();
    void clear();
    void clearToWall();
    void load(QVector<unsigned short int> level);  //levels
    unsigned short int get(unsigned short int y, unsigned short int x);
    QVector<unsigned short int> getBoardToVector();
    void set(unsigned short int y, unsigned short int x,unsigned short int a);
    short int pos_Steve_x;
    short int pos_Steve_y;                  //position Steve
    short int pos_arrow_x;
    short int pos_arrow_y;                  //position arrow up||down||left||right
    short int pos_Teleport_x;      //teleportation position near the arrow
    short int pos_Teleport_y;
    short int pos_Teleport_x_next; //teleportation position far the arrow
    short int pos_Teleport_y_next;
    bool isWin();                           //we check if we won
private:
    OneCell myBoard[13][15];                            // y=13 x=15
};

#endif // BOARD_H
