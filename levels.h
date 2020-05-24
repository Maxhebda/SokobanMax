#ifndef LEVELS_H
#define LEVELS_H

class Levels
{
public:
    static unsigned short int level00[13*15];
    static unsigned short int level01[13*15];
    static unsigned short int level02[13*15];
    Levels();
    static unsigned short int * basicLevel(unsigned short int nr);
};

#endif // LEVELS_H
