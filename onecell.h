#ifndef ONECELL_H
#define ONECELL_H


class OneCell
{
public:
    OneCell();
    static const unsigned short int CELL_EMPTY = 0;
    static const unsigned short int CELL_STEVE = 1;
    static const unsigned short int CELL_DIAMOND = 2;
    static const unsigned short int CELL_HOLE = 3;
    static const unsigned short int CELL_DIAMONDinHOLE = 4;
    static const unsigned short int CELL_WALL = 5;
    static const unsigned short int CELL_DOOR = 10;
    static const unsigned short int CELL_ARROW_UP = 20;
    static const unsigned short int CELL_ARROW_DOWN = 21;
    static const unsigned short int CELL_ARROW_LEFT = 22;
    static const unsigned short int CELL_ARROW_RIGHT = 23;
    static const unsigned short int CELL_STEVEinHOLE = 31;

    void set(unsigned short int);
    unsigned short int get();

private:
    unsigned short int nr;
};

#endif // ONECELL_H
