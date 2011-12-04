#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_LEN 1024

void do_merge(int *arr, int p, int q, int r, int *ass)
{
    int i = p;
    int j = q + 1;
    int k = p;

    while(i <= q && j <= r) {
        if(arr[i] < arr[j]) {
            ass[k++] = arr[i++];
        } else {
            ass[k++] = arr[j++];
        }
    }

    while(i <= q) {
        ass[k++] = arr[i++];
    } 

    while(j <= r) {
        ass[k++] = arr[j++];
    }

    for(i = p; i <= r; i++) {
        arr[i] = ass[i];
    }
}


void do_merge_sort(int *arr, int begin, int end, int *ass)
{
    if(begin < end) {
        int mid = (begin + end) / 2;
        do_merge_sort(arr, begin, mid, ass);
        do_merge_sort(arr, mid + 1, end, ass);
        do_merge(arr, begin, mid, end, ass);
    }
}

void merge_sort(int *arr, int length)
{
    int ass[MAX_ARRAY_LEN];
    do_merge_sort(arr, 0, length - 1, ass);
}

int main()
{
    int arr[] = {3, 7, 6, 9, 8, 21, 10, 32, 18};
    merge_sort(arr, 9);
    for(int i = 0; i < 9; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
