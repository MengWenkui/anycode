#include <stdio.h>
#include <stdlib.h>

void put_egg(int m, int n, int level, int egg[]) 
{
	if(n == 1) {
		if(level > 0 && m < egg[level-1])
			return;
		egg[level] = m;
		
		int j;
		for(j = 0; j <= level; j++) {
			printf("%d ", egg[j]); 
		}
		printf("\n");
		return;
	}
	
	int i = 1;
	if(level > 0)
		i = egg[level-1];
	for(; i <= m - n + 1; i++) {
		egg[level] = i;	
		put_egg(m - i, n - 1, level + 1, egg);
	}
}

int main(int argc, char* argv[])
{
	if(argc != 3) {
		printf("egg m n\n");
		return 0;
	}
		
	int egg[20];
	put_egg(atoi(argv[1]), atoi(argv[2]), 0, egg);
	return 0;
}
