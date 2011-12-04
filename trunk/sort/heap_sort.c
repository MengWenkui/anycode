#include <stdio.h>
#include <stdlib.h>

void array_print(int *arr, int len)
{
     for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



void simple_exchange(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void max_heapify(int *arr, int len, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if(l < len && arr[largest] < arr[l]) {
        largest = l;
    }

    if(r < len && arr[largest] < arr[r]) {
        largest = r;
    }

    if(largest != i) {
        simple_exchange(arr, i, largest);
        max_heapify(arr, len, largest);
    }
}

void build_max_heap(int *arr, int len) 
{
    for(int i = len/2; i >= 0; i--) {
        max_heapify(arr, len, i);
    }
}

void heap_sort(int *arr, int len) 
{
    build_max_heap(arr, len);
    for(int i = len - 1; i > 0; i--) {
        simple_exchange(arr, i, 0);
        max_heapify(arr, i, 0);
    }
}


int main()
{
    int arr[] = {3, 7, 6, 9, 8, 21, 10, 32, 18};
    heap_sort(arr, 9);
    array_print(arr, 9);
    return 0;

}
