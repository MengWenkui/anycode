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
			for(i=k;i<n-span;i+=span)//ѭ���������еĵ����ڶ���Ԫ�أ�
				//��Ϊ���һ��Ԫ����СΪn-span,��󲻿�����n����
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