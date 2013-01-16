/*
 * ������Ԫ�طֳɷǿյ���������P, Q
 * ��ӡ���п��ܵ����
 *
 * ����C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n;
 * ȥ���յļ��ϣ�1��2^n-2���������ĵ�nλλͼ���ܱ�ʾ����
 *
 * ��6��Ԫ��Ϊ��
 * 1�ĵ�6λΪ000001, ����һ������ѡ�����һ��Ԫ��
 * 3�ĵ�6λΪ000011, ����һ������ѡ���������Ԫ��
 *
 * ͨ�����ַ�ʽ��������O(2^n)�ĸ��Ӷ���C(n, r)���
 * ��0��2^n-2����ж�λͼ��1�ĸ�����Ϊr���������
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print(char *array, int num)
{
    int i;
    for(i = 0; i < num; i++)
        printf("%c ", array[i]);
    printf("\n");
}

void process(char *array, int cur, int num, char *p, char *q)
{
    int i;
    int b = 1 << (num - 1);
    int pi = 0;
    int qi = 0;
    for(i = 0; i < num; i++) {
        if(cur & b)
            p[pi++] = array[i];
        else
            q[qi++] = array[i];
        b >>= 1;
    }

    printf("Values in P: ");
    print(p, pi);
    printf("Values in Q: ");
    print(q, qi);
    printf("\n");
}

void partition(char *array, int num)
{
    int i;
    int last = (int)pow(2, num);
    char *p = (char*)malloc(sizeof(char) * num);
    char *q = (char*)malloc(sizeof(char) * num);

    for(i = 1; i < last - 1; i++) {
        process(array, i, num, p, q);
    }

    printf("Total = %d\n", last - 2);

    free(p);
    free(q);
}

int main()
{
    char array[] = "ABC";
    partition(array, 3);
    return 0;
}
