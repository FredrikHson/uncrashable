#include "lib.h"
#include <stdio.h>

void libfunc()
{
    int r = rand() % 2;

    if(r == 0)
    {
        int* i = 0;
        *i = 1;
    }
    else
    {
        printf("inside fun2 rand %i\n", r);
    }
}
