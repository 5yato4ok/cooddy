#include <stdio.h>
#include <stdarg.h>


int foo(wchar_t* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    int ret = vfwscanf(stdin, format, arglist);
    va_end(arglist);
    return ret;
}

void bar() {
    int buffer[10] = {0};
    int a, b;
    int ret = foo(L"%d%d", &a, &b);
    buffer[a];      // error here
    buffer[b];      // error here
}