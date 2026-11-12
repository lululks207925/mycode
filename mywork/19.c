/*计算最小公倍数

从键盘输入两个正整数，计算并输出两个数的最小公倍数。

要求：计算最大公约数的功能，由自定义函数完成。*/
#include<stdio.h>
int gb(int x,int y);
int main()
{int n,m,x,t;
 scanf("%d%d",&n,&m);
 t=n*m;
 x=gb(n,m);
 printf("%d",t/x);
 return 0;
}
int gb (int x,int y)
{int s;
 
 s=x%y;
 while(s!=0)
 {x=y;
  y=s;
  s=x%y;
  
 }
  return y;
  
  
}