#include "onecell.h"

OneCell::OneCell()
{
    nr = 0;
}

unsigned short int OneCell::get()
{
    return nr;
}

void OneCell::set(unsigned short int a)
{
    nr = a;
}
