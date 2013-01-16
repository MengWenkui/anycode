#include<stdio.h>
typedef int datatype;
#define N 10
void insertsort(datatype a[],int n)
{
	int i,j;
	datatype temp;
	for(i=0;i<n-1;i++)
	{
		temp=a[i+1];
		j=i;
		while(j>=0&&a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
void main()
{
	datatype a[N];
	int i;
	for(i=0;i<N;i++)
		scanf("%d",&a[i]);
	insertsort(a,N);
	for(i=0;i<N;i++)
		printf("%d ",a[i]);
	printf("\n");
}


