 /*分析：设R= {r1,r2,r3,……，rn}是要进行排列的n个元素，Ri=R-{ri}。集合X中的元素的全排列记为perm(X).(ri)perm(X)表示在全排列perm(X)的每一个排列前加上前缀ri得到的排列，R的全排列可归纳定义如下：

当n=1，perm(R) = (r) ,其中r是集合R中唯一的元素。

当n>1，perm(R)由(r1)perm(R1),(r2)perm(R2),……,(rn)perm(Rn)构成。因此可以有如下算法：
*/
 #include <stdio.h>
 #include <stdlib.h>


 /*
  函数：swap ， 交换数组中两个元素的位置
  参数：数组， 起始下标，终止下标
  返回：void
 */
 void swap( int *a , int i , int j ) ;

  /*
  函数：perm ，全排列
  参数：数组， 起始下标，终止下标
  返回：void
 */
 void perm( int *a , int k , int m ) ;
int main()
 {
     int array[4] = { 1, 2, 3, 4 } ;
     perm( array , 0 , 3 ) ;
 }


 void swap( int *a , int i , int j )
 {
     int temp ;
     temp = *(a+i) ;
     *(a+i) = *( a+j ) ;
     *( a+j ) = temp ;
 }

 void perm( int *a , int k , int m )
 {
     int i ;
     /*单元素排列，直接输出*/
     if( k == m )
     {
         for( i = 0 ; i <= m ; i ++ )
         {
             printf("%d ", *(a+i) ) ;
         }
         printf("\n");
     }

     else
     {
         for( i = k ; i <= m ; i ++ )
         {
             swap( a , k , i ) ;
             perm( a ,k+1 ,m ) ;
             swap( a , k , i ) ;
         }
     }
 }


