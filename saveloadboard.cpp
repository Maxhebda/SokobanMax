#include "saveloadboard.h"

SaveLoadBoard::SaveLoadBoard()
{
    allTheBoards.clear();
}

void SaveLoadBoard::addNewBoard(QVector<unsigned short int> b)
{
    for (auto iter=b.begin();iter!=b.end();iter++)
    {
        allTheBoards.push_back(*iter);
    }
}
