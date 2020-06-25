#include "saveloadboard.h"

SaveLoadBoard::SaveLoadBoard()
{
    clearAll();
}

void SaveLoadBoard::clearAll()
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

void SaveLoadBoard::getBoardToTable(unsigned short index, char (&table)[13][15])
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            table[y][x]=allTheBoards[index*13*15 + y*15+x];
        }
    }
}

bool SaveLoadBoard::boardIsGood(char (&table)[13*15])
{
    char counterSteve=0;
    char counterDiamond=0;
    char counterHole=0;
    char counterDiamondWithoutHole=0;
    char counterArrow=0;
    for (unsigned short int i=0; i<13*15; i++)
    {
            switch (table[i]) {
                case OneCell::CELL_HOLE : counterHole++;break;
                case OneCell::CELL_STEVE : counterSteve++;break;
                case OneCell::CELL_DIAMOND : {counterDiamond++; counterDiamondWithoutHole++;} break;
                case OneCell::CELL_DIAMONDinHOLE : {counterHole++; counterDiamond++;} break;
                case OneCell::CELL_ARROW_UP : counterArrow++;break;
                case OneCell::CELL_ARROW_DOWN : counterArrow++;break;
                case OneCell::CELL_ARROW_RIGHT : counterArrow++;break;
                case OneCell::CELL_ARROW_LEFT : counterArrow++;break;
            }
    }
    if (counterSteve!=1 || counterArrow>1 || counterHole<1 || counterDiamond!=counterHole || counterDiamondWithoutHole==0)
    {
        return false;
    }
    return true;
}

unsigned short int SaveLoadBoard::saveToFile(QString fileName)
{
    char table[13][15];
    FILE * fileWrite = fopen(fileName.toStdString().c_str(),"wb");     //open file to save binary
    for (unsigned short int i=0; i<counterLevels ; i++)
    {
        if (dynamicLevelsMenuStar[i]!='*')                             //save only full boards
        {
            //---- save level/index in table ----
            getBoardToTable(i,table);
            fwrite(&table,sizeof(table),1,fileWrite);                 //save to file (all full boards)
        }
    }
    fclose(fileWrite);
    return 0;
}

unsigned short int SaveLoadBoard::openFromFile(QString fileName)
{
    // -- clear all data --
    //    allTheBoards.clear();
    //    counterLevels=0;
    //    dynamicLevelsMenu=0;
    //    dynamicLevelsMenuStar.clear();
    unsigned short int tempCounter=0;
    QVector<char> tempBoards;
    unsigned short int i;
    tempBoards.clear();
    // -- read from file --
    char table[13*15];
    FILE * fileRead = fopen(fileName.toStdString().c_str(),"rb");     //open file to read binary
    while (fread(&table,1,13*15,fileRead)==13*15)
    {
        tempCounter++;
        for (i=0;i<13*15;i++)
        {
            tempBoards.push_back(table[i]);
        }
    }
    fclose(fileRead);
    if (tempCounter==0)
        return 1; // = error
    // ---------------- updating the board database ------------------
    for (unsigned short int c=0;c<tempCounter;c++)
    {
        for (unsigned short int t=0;t<13*15;t++)
        {
            table[t]=tempBoards[c*13*15+t];
        }
        if (SaveLoadBoard::boardIsGood(table)==false)
            return 2; // error
    }
    // ---------------- updating the board database ------------------
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
