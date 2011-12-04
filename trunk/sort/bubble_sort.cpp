#include<stdio.h>
void bubblesort(int a[],int n)
{
	int i,j,flag=1,temp;

	for(i=1;i<n&&flag==1;i++)
	{	
		flag=0;
		for(j=0;j<n-i;j++)
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				flag=1;
			}						
	}
}
void main()
{
	int a[10]={12,32,8,25,31,27,16,14,9,10};
	int i;
	bubblesort(a,10);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
    
}