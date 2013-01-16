#include <stdio.h>
int main()
{
    int tt = 1;
    char *c = (char*)(&tt);
    if(*c)
    {
        printf("litte endian\n");
    }
    else
    {
        printf("big endian\n");
    }
    return 0;
}
