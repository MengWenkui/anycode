 /*��������R= {r1,r2,r3,������rn}��Ҫ�������е�n��Ԫ�أ�Ri=R-{ri}������X�е�Ԫ�ص�ȫ���м�Ϊperm(X).(ri)perm(X)��ʾ��ȫ����perm(X)��ÿһ������ǰ����ǰ׺ri�õ������У�R��ȫ���пɹ��ɶ������£�

��n=1��perm(R) = (r) ,����r�Ǽ���R��Ψһ��Ԫ�ء�

��n>1��perm(R)��(r1)perm(R1),(r2)perm(R2),����,(rn)perm(Rn)���ɡ���˿����������㷨��
*/
 #include <stdio.h>
 #include <stdlib.h>


 /*
  ������swap �� ��������������Ԫ�ص�λ��
  ���������飬 ��ʼ�±꣬��ֹ�±�
  ���أ�void
 */
 void swap( int *a , int i , int j ) ;

  /*
  ������perm ��ȫ����
  ���������飬 ��ʼ�±꣬��ֹ�±�
  ���أ�void
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
     /*��Ԫ�����У�ֱ�����*/
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


