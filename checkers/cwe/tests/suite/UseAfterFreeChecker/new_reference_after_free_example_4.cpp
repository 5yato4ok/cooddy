#include <stdlib.h>

int main ()
{
    int * a;
    a = (int*) malloc (100*sizeof(int));
    free(a);

    int b = 12;
    b = b + *a;
    a = (int*) malloc (50*sizeof(int));
    b += *a;
    return b;
}
