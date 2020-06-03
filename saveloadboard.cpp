#include "saveloadboard.h"

SaveLoadBoard::SaveLoadBoard()
{
    allTheBoards.clear();
    counterLevels=0;
}

void SaveLoadBoard::addBoard(QVector<unsigned short int> board,unsigned short int index)
{
    if (index==0 && counterLevels==0)           // if storage is empty
    {
        addNewBoard(board);
    }
    else
        if (index<=counterLevels-1)
        {
            for (unsigned short int y=0; y<13; y++)
            {
                for (unsigned short int x=0; x<15; x++)
                {
                    allTheBoards[index*13*15 + y*15+x] = board[y*15+x];
                }
            }
        }
}

void SaveLoadBoard::addNewBoard(QVector<unsigned short int> board)
{
    counterLevels++;
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            allTheBoards.push_back(board[y*15+x]);
        }
    }
}

void SaveLoadBoard::addNewBoard()
{
    counterLevels++;
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            allTheBoards.push_back(0);
        }
    }
}

unsigned short int SaveLoadBoard::getCounterLevels()
{
    return counterLevels;
}
