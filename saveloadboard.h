#ifndef SAVELOADBOARD_H
#define SAVELOADBOARD_H
#include <QVector>

class SaveLoadBoard
{
public:
    SaveLoadBoard();
    QVector<unsigned short int> getBoard(unsigned short int index);         //13*15 elements
    void addBoard(QVector<unsigned short int>,unsigned short int index);    //add active board to allTheBoard to index
    void deleteBoard(unsigned short int index);
    void addNewBoard(QVector<unsigned short int>);                          //add active board to allTheBoard to the end
    void addNewBoard();                                                     //add empty  board to allTheBoard to the end
    unsigned short int getCounterLevels();                                  //counter levels in memory (in allTheBoards)
    bool isEmpty();                                                         //true if all is "*"
    void getBoardToTable(unsigned short int index, char (&table)[13][15]);

    //------- name dynamic board container --------------
    unsigned short int dynamicLevelsMenu;
    QVector <char>     dynamicLevelsMenuStar;    // ? "*"

    unsigned short int saveToFile(QString fileName);                        //0=ok, nr = error
    unsigned short int openFromFile(QString fileName);                      //0=ok, nr = error
private:
    QVector<unsigned short int> allTheBoards;                               //MEMORY  13*15 elements * x levels
    unsigned short int counterLevels;
};

#endif // SAVELOADBOARD_H
