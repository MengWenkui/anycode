/*
 * 将数组元素分成非空的两个集合P, Q
 * 打印所有可能的情况
 *
 * 根据C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n;
 * 去掉空的集合，1到2^n-2的所有数的低n位位图即能标示集合
 *
 * 以6个元素为例
 * 1的低6位为000001, 代表一个集合选了最后一个元素
 * 3的低6位为000011, 代表一个集合选了最后两个元素
 *
 * 通过这种方式，可以以O(2^n)的复杂度求C(n, r)组合
 * 从0到2^n-2逐个判断位图中1的个数，为r则符合条件
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
