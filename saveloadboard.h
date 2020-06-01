#ifndef SAVELOADBOARD_H
#define SAVELOADBOARD_H
#include <QVector>

class SaveLoadBoard
{
public:
    SaveLoadBoard();
    QVector<unsigned short int> get(unsigned short int level);  //13*15 elements
    void addNewBoard(QVector<unsigned short int>);              //add active board to allTheBoard
private:
    QVector<unsigned short int> allTheBoards;                   //13*15 elements * x levels
    unsigned short int counterLevels;
};

#endif // SAVELOADBOARD_H
