#!/usr/bin/python


def find_nth(array1, array2, length):
    t = (length + 1) / 2
    if(length == 1):
        return min(array1[t-1], array2[t-1])
    if(array1[t-1] <= array2[t-1]):
        return find_nth(array1[t:], array2, length - t)
    else:
        return find_nth(array1, array2[t:], length - t)

def find_nth2(array1, array2, length):
    low1 = low2 = 0
    high1 = high2 = length
    while(length >= 1):
        t = (length + 1) / 2
        if(length == 1):
            return min(array1[low1 + t - 1], array2[low2 + t - 1])
        if(array1[low1 + t - 1] <= array2[low2 + t - 1]):
            low1 = t
            length -= t
        else:
            low2 = t
            length -= t
    return min(array1[low1 + t - 1], array2[low2 + t - 1])

array1 = [1, 5, 8, 50, 198]
array2 = [3, 18, 29, 87, 107]
print find_nth(array1, array2, len(array1))
print find_nth2(array1, array2, len(array1))

array1.append(200)
array2.append(150)
print find_nth(array1, array2, len(array1))
print find_nth2(array1, array2, len(array1))
