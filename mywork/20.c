/*找出满足abc=a!+b!+c!的所有三位数。一行输出的数据之间用一个空格隔开。*/

#include<stdio.h>
int jc(int x);
int main()
{int i,x,x1,x10,x100;
 for(i=100;i<1000;i++)
 {x=i;
   x1=x%10;
  x10=x/10%10;
  x100=x/100;
   if(jc(x1)+jc(x10)+jc(x100)==x)
   printf("%d ",i);
   
 }
  
  
 return 0;
}
int jc(int x)
{if(x<=1)
  return 1;
 else
   return x*jc(x-1); 
}  
  

