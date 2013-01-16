/*
大概的转换步骤：

1，首先选出64个字符，包括大小写字母(a-z,A-Z)，数字(0-9)和符号'+','/'作为一个集合(其实加上作为padding的'='该是65个字符)。

2，然后，按(3*8=4*6)每3个8位字节转化为4个6位的字节(高2位补0)的形式,将输入的字节序列都转换成只包含base64集合中的字符的另一个字节序列，如下简图:

转换前：
.--------+--------+--------.
|aaaaaabb|bbbbcccc|ccdddddd|
`--------+--------+--------`

转换后：
.--------+--------+--------+--------.
|00aaaaaa|00bbbbbb|00cccccc|00dddddd|
`--------+--------+--------+--------'

3，若输入字节数不是3的倍数，余1位则将其转换后补2个padding('='),余2位转换后补1个padding。


4，编码后的字符每76个占一行，至于换行符，Unix系用的LF('\n'),Windows用的是CRLF('\r''\n')，见wiki对于newline的解释。

*/


#include <stddef.h>
#include <malloc.h>

/* 若需控制内存分配(如内存池)，定义此宏*/
#ifndef BASE64_ALLOCATE
#define BASE64_ALLOCATE(bytes)    malloc(bytes)
#endif

/* 参数为0则返回NULL */
#define     CHECK_RETRUN(value)     do{if(0 == (value)) return NULL;}while(0) 

#define     IS_BASE64VALUE(ch)      (base64_index_char[ch] >= 0)
#define     IS_IGNORABLE(ch)        ((ch) == '\n' || (ch) == '\r')  /* ignore CRLF */

#define     BASE64_LINE             76

/* base64字符集合 */
static const char   base64_alphabet[] = 
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',   /*  0- 9 */
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',   /* 10-19 */
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',   /* 20-29 */
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',   /* 30-39 */
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',   /* 40-49 */
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',   /* 50-59 */
    '8', '9', '+', '/'                                  /* 60-63 */
};

/* 解码表 */
static const char   base64_index_char[128] = 
{
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  /*  0-15 */
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  /*  16-31 */
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,  /*  32-47 ('+', '/'   */
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,  /*  48-63 ('0' - '9') */
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,  /*  64-79 ('A' - 'Z'  */
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,  /*  80-95 */
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,  /*  96-111 ('a' - 'z') */
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, -1, -1, -1, -1,  /*  112-127 */
};


/*
* 对bytes个字节的ptext编码，返回编码后的字节序列
*/
char*   base64_encode(const char* ptext, size_t bytes)
{
    size_t      loop = bytes / 3;
    size_t      buf_size = 4 * ((bytes + 2) / 3) ; 
    char*       pbuf;
    char*       pos; /* to skip CRLF */
    char*       ret;

    CHECK_RETRUN(ptext);
    CHECK_RETRUN(bytes);
    buf_size += buf_size / 76;  /* CRLF length  */
    ret = pos = pbuf = (char*)BASE64_ALLOCATE(buf_size + 1);
    CHECK_RETRUN(pbuf);


    /* 处理编码转换的部分 */        
    while (loop--)
    {
        pbuf[0] = base64_alphabet[ptext[0] >> 2];
        pbuf[1] = base64_alphabet[(ptext[0] & 0x03) << 4 | ptext[1] >> 4];
        pbuf[2] = base64_alphabet[(ptext[1] & 0x0F) << 2 | ptext[2] >> 6];
        pbuf[3] = base64_alphabet[ptext[2] & 0x3F];
        pbuf += 4;
        ptext += 3;

        if (pbuf - pos == BASE64_LINE) /* 检查是否应该换行 */
        {
            *pbuf++ = '\n';
            pos = pbuf;
        }
    }
    /* 对于最后"特殊"字节的处理*/
    switch(bytes % 3)
    {
    case 1:
        pbuf[0] = base64_alphabet[ptext[0] >> 2];
        pbuf[1] = base64_alphabet[ptext[0] << 4 & 0x30];
        pbuf[2] = '=';
        pbuf[3] = '=';
        break;

    case 2:
        pbuf[0] = base64_alphabet[ptext[0] >> 2];
        pbuf[1] = base64_alphabet[(ptext[0] << 4 & 0x30) | ptext[1] >> 4];
        pbuf[2] = base64_alphabet[ptext[1] << 2 & 0x3C];
        pbuf[3] = '=';
        break;

    default:
        break;
    }
    *pbuf = '\0';  /* null terminated */
    return ret; 
}

/*
* 对bytes个字节的ptext解码，返回解码后的字节序列
*/
char*     base64_decode(const char* ptext, size_t bytes)
{
    size_t      buf_size = 3 * (bytes - bytes/(BASE64_LINE+1)) / 4;
    const char* end = ptext + bytes; 
    char*       pbuf;
    char*       ret;    
    char        quad[4] = {0}; /*四个字节一组 */
    char        byte;
    int         cnt;

    CHECK_RETRUN(ptext);
    CHECK_RETRUN(bytes);
    ret = pbuf = (char*)BASE64_ALLOCATE(buf_size + 1);
    CHECK_RETRUN(pbuf);

    do
    {
        cnt = 0;
        while (cnt < 4)
        {
            byte = *ptext++;

            if (IS_BASE64VALUE(byte) && !IS_IGNORABLE(byte))
            {
                quad[cnt++] = base64_index_char[byte];
            }
        }
        /* 解码部分 */
        pbuf[0] = quad[0] << 2 | quad[1] >> 4;
        pbuf[1] = quad[1] << 4 | quad[2] >> 2;
        pbuf[2] = quad[2] << 6 | quad[3];
        pbuf += 3;
    }while (ptext < end);

    *pbuf = '\0';  /* null terminated */
    return ret;
}