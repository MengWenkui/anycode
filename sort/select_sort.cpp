#include<stdio.h>
void selectsort(int a[],int n)
{
	int i,j,small,temp;
	for(i=0;i<n-1;i++)
	{
		small=i;
		for(j=i+1;j<n;j++)
			if(a[j]<a[small])
				small=j;
			if(small!=i)
			{
				temp=a[small];
				a[small]=a[i];
				a[i]=temp;
			}
		  
				
	}
}
void main()
{
	int a[10]={12,32,8,25,31,27,16,14,9,10};
	int i;
	selectsort(a,10);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
    
}