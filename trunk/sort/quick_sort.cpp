#include<stdio.h>
void quicksort(int a[],int n,int low,int high)
{
	int i=low,j=high,temp=a[low];
    while(i<j)
	{
		while(i<j&&a[j]>=temp)j--;
		if(i<j)
		{
			a[i]=a[j];
			i++;
		}
		while(i<j&&a[i]<temp)i++;
		if(i<j)
		{
			a[j]=a[i];
			j--;
		}
	
	}
	a[i]=temp;
	if(low<i)quicksort(a,n,low,i-1);
	if(i<high)quicksort(a,n,i+1,high);
	
}
void main()
{
	int a[10]={12,32,8,25,31,27,16,14,9,10};
	int i;
	quicksort(a,10,0,9);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
    
}