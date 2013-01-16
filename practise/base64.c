/*
��ŵ�ת�����裺

1������ѡ��64���ַ���������Сд��ĸ(a-z,A-Z)������(0-9)�ͷ���'+','/'��Ϊһ������(��ʵ������Ϊpadding��'='����65���ַ�)��

2��Ȼ�󣬰�(3*8=4*6)ÿ3��8λ�ֽ�ת��Ϊ4��6λ���ֽ�(��2λ��0)����ʽ,��������ֽ����ж�ת����ֻ����base64�����е��ַ�����һ���ֽ����У����¼�ͼ:

ת��ǰ��
.--------+--------+--------.
|aaaaaabb|bbbbcccc|ccdddddd|
`--------+--------+--------`

ת����
.--------+--------+--------+--------.
|00aaaaaa|00bbbbbb|00cccccc|00dddddd|
`--------+--------+--------+--------'

3���������ֽ�������3�ı�������1λ����ת����2��padding('='),��2λת����1��padding��


4���������ַ�ÿ76��ռһ�У����ڻ��з���Unixϵ�õ�LF('\n'),Windows�õ���CRLF('\r''\n')����wiki����newline�Ľ��͡�

*/


#include <stddef.h>
#include <malloc.h>

/* ��������ڴ����(���ڴ��)������˺�*/
#ifndef BASE64_ALLOCATE
#define BASE64_ALLOCATE(bytes)    malloc(bytes)
#endif

/* ����Ϊ0�򷵻�NULL */
#define     CHECK_RETRUN(value)     do{if(0 == (value)) return NULL;}while(0) 

#define     IS_BASE64VALUE(ch)      (base64_index_char[ch] >= 0)
#define     IS_IGNORABLE(ch)        ((ch) == '\n' || (ch) == '\r')  /* ignore CRLF */

#define     BASE64_LINE             76

/* base64�ַ����� */
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

/* ����� */
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
* ��bytes���ֽڵ�ptext���룬���ر������ֽ�����
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


    /* �������ת���Ĳ��� */        
    while (loop--)
    {
        pbuf[0] = base64_alphabet[ptext[0] >> 2];
        pbuf[1] = base64_alphabet[(ptext[0] & 0x03) << 4 | ptext[1] >> 4];
        pbuf[2] = base64_alphabet[(ptext[1] & 0x0F) << 2 | ptext[2] >> 6];
        pbuf[3] = base64_alphabet[ptext[2] & 0x3F];
        pbuf += 4;
        ptext += 3;

        if (pbuf - pos == BASE64_LINE) /* ����Ƿ�Ӧ�û��� */
        {
            *pbuf++ = '\n';
            pos = pbuf;
        }
    }
    /* �������"����"�ֽڵĴ���*/
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
* ��bytes���ֽڵ�ptext���룬���ؽ������ֽ�����
*/
char*     base64_decode(const char* ptext, size_t bytes)
{
    size_t      buf_size = 3 * (bytes - bytes/(BASE64_LINE+1)) / 4;
    const char* end = ptext + bytes; 
    char*       pbuf;
    char*       ret;    
    char        quad[4] = {0}; /*�ĸ��ֽ�һ�� */
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
        /* ���벿�� */
        pbuf[0] = quad[0] << 2 | quad[1] >> 4;
        pbuf[1] = quad[1] << 4 | quad[2] >> 2;
        pbuf[2] = quad[2] << 6 | quad[3];
        pbuf += 3;
    }while (ptext < end);

    *pbuf = '\0';  /* null terminated */
    return ret;
}