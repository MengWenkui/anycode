#include<stdio.h>
int d[10]={1,2,3,5,7,11,13,17,19,23};
void shellsort(int a[],int n,int d[],int num)
{
	int i,j,k,m,span,temp;
	for(m=num-1;m>=0;m--)
	{
		span=d[m];
		for(k=0;k<span;k++)
		{
			for(i=k;i<n-span;i+=span)//循环到该序列的倒数第二个元素，
				//因为左后一个元素做小为n-span,最后不可能留n个空
			{
				temp=a[i+span];
				j=i;
				while(j>-1&&a[j]>temp)
				{
					a[j+span]=a[j];
					j-=span;
				}
				a[j+span]=temp;
			}
		}


	}

}
void main()
{
	int a[10]={12,32,8,25,31,27,16,14,9,10};
	int i;
	shellsort(a,10,d,10);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
    
}