/*斐波那契数列



从键盘输入一个正整数，记作n，计算并输出斐波那契数列的第n项。



输入：

4

输出：

3*/
#include<stdio.h>
int main()
{int x,n;
 int a=1,b=1,c;
 scanf("%d",&n);

 for(x=3;x<=n;x++)
 {c=a+b;
  a=b;
  b=c;
 }
   
 
 printf("%d",b);
  
  
  return 0;
}