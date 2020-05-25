#ifndef LEVELS_H
#define LEVELS_H
#include <QVector>

class Levels
{
public:
    static unsigned short int level00[13*15];
    static unsigned short int level01[13*15];
    static unsigned short int level02[13*15];
    static unsigned short int level03[13*15];
    static unsigned short int level04[13*15];
    static unsigned short int level05[13*15];
    static unsigned short int level06[13*15];
    Levels();
    static QVector<unsigned short int> basicLevel(unsigned short int nr);
};

#endif // LEVELS_H
