/*计算π的值

用公式π/4=1-1/3+1/5-1/7...计算π的近似值，直到发现某一项的绝对值小于10^6为止（该项不累加）。



直接输出计算得到的π的值。*/
#include<stdio.h>
int main()
{int n;
 double x,sum=0,P;
for(n=1; ;n++)
{x=1.0/(2*n-1);
 if(x<1e-6)
 {
   break;
 }
 if(n%2==1)
 sum=sum+x;
  else
    sum=sum-x;
    
}
 P=4.0*sum;
 printf("%f",P);
  return 0;
}