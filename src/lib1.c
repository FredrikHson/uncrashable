#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

void libfunc()
{
    int r = rand() % 50;

    if(r == 0)
    {
        int* i = 0;
        *i = 1;
    }
    else
    {
        printf("inside fun1 rand %i\n", r);
    }
}
