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

QVector<unsigned short int> SaveLoadBoard::getBoard(unsigned short int index)
{
    QVector<unsigned short int> tmp;
    if (index<counterLevels)
    {
        for (unsigned short int y=0; y<13; y++)
        {
            for (unsigned short int x=0; x<15; x++)
            {
                tmp.push_back(allTheBoards[index*13*15 + y*15+x]);
            }
        }
    }
    else
    {
        for (unsigned short int y=0; y<13; y++)
        {
            for (unsigned short int x=0; x<15; x++)
            {
                tmp.push_back(0);
            }
        }
    }
    return tmp;
}

void SaveLoadBoard::deleteBoard(unsigned short int index)
{
    if (index<0 || index>counterLevels-1 || counterLevels==0)
        return;

    counterLevels--;
    allTheBoards.remove(index*13*15,13*15);
}

unsigned short int SaveLoadBoard::saveToFile(QString fileName)
{
    return 0;
}

bool SaveLoadBoard::isEmpty()
{
    bool tmp = true;
    if (counterLevels==0) return true;
    for(auto iter=dynamicLevelsMenuStar.begin();iter!=dynamicLevelsMenuStar.end();iter++)
    {
        if (*iter!='*')
        {
            tmp=false;
            break;
        }
    }
    return tmp;
}
