#!/usr/local/bin/python

total = 226
counter = []
stat = []
result = open("../result.txt", "r")

while (True) :
    line = result.readline()
    if(line == '') :
        break
    line = line[0:len(line)-1]
    counter.append(int(line))

result.close()

for i in range(0, 101, 5) :
    stat.append(0)

for i in counter :
    idx = int(i * 20 / total)
    for j in range(idx, len(stat)) :
        stat[j] += 1

print stat

outfile = open("counting.xls", "w+")
for i in stat :
    outfile.writelines(str(i))
    outfile.writelines("\t")
outfile.close()
