#!/usr/bin/python


def find_nth(array1, array2, length):
    t = length / 2
    if(t == 0):
        t = 1
    if(length == 1):
        return min(array1[t-1], array2[t-1])
    if(array1[t-1] <= array2[t-1]):
        return find_nth(array1[t:], array2, length - t)
    else:
        return find_nth(array1, array2[t:], length - t)

array1 = [1, 5, 8, 50, 198]
array2 = [3, 18, 29, 87, 107]
print find_nth(array1, array2, len(array1))

array1 += [200]
array2 += [150]
print find_nth(array1, array2, len(array1))
