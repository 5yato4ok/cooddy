int main()
{
#ifdef NULLPTR_123
    int *p = 0;
    *p;
#endif

#ifdef DIVIDE_BY_ZERO
    int c = 123 / 0;
#endif
    return 0;
}