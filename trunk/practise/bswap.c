/*
     usage: to convert between the form of big-endian and little-endian
     author: ydzhang
     date: 2008Äê12ÔÂ6ÈÕ20:23:48
*/
#include <stdio.h>
typedef unsigned int u32;
typedef unsigned short u16;

#define BSWAP_16(x) \
        (u16) ( ((((u16)(x) & 0x00ff)) << 8)   \
        | (((u16)(x) & 0xff00) >> 8) )

u16 bswap_16(u16 x)
{
    return ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
}

u32 bswap_32(u32 x)
{
    return ((x & 0x000000ff) << 24) |
           ((x & 0x0000ff00) << 8)  |
           ((x & 0x00ff0000) >> 8)  |
           ((x & 0xff000000) >> 24);
}

int main()
{
    u16 num_16 = 0x1234;
    u32 num_32 = 0x12345678;

    printf("%x\n", bswap_16(num_16));
    printf("%x\n", BSWAP_16(num_16));
    printf("%x\n", bswap_32(num_32));
    return 0;
}
