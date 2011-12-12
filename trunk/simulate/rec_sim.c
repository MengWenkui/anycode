#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

int count_1 = 0;
int count_2 = 0;

void rec(int n)
{
    count_1++;
    if(n == 0) {
        return;
    }
    rec(n-1);
}

void rec2(int n)
{
    count_2++;
    if(n / 2 == 0) {
        return;
    }

    rec2(n/2);
    rec2(n/2);
}

int main(int argc, char *argv[])
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    rec(atoi(argv[1]));
    gettimeofday(&end, NULL);

    uint64_t val = (end.tv_sec - start.tv_sec) * 1000000
        + end.tv_usec - start.tv_usec;
    printf("%lluus\n", val);
    printf("%d\n", count_1);

    gettimeofday(&start, NULL);
    rec2(atoi(argv[2]));
    gettimeofday(&end, NULL);
    val = (end.tv_sec - start.tv_sec) * 1000000
        + end.tv_usec - start.tv_usec;

    printf("%lluus\n", val);

    printf("%d\n", count_2);
    return 0;
}
