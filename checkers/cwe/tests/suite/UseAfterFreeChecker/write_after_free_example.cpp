#include <iostream>
#include <stdlib.h>

int main ()
{
    int * a;
    a = (int*) malloc (100*sizeof(int));
    free(a);
    int b = 12;
    *a = b + 15;
    return b;
}
