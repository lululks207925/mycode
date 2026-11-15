/*求sinx值

编写程序，利用sinx=x-x^3/3！+x^5/5！-x^7/7！+x^9/9！……计算sinx的值，直到最后一项小于10-6为止（n!编写函数实现）。
*/
#include<stdio.h>
#include<math.h>
double jc(int x);
int main()
{int x,n;
 double t,s=0;
 scanf("%d",&x);
 for(n=1; ;n++)
 {t=pow(x,(2*n-1))/jc(2*n-1);
  if(t<1e-6)
    break;
  if(n%2==1)
    s=s+t;
  else
    s=s-t;
 }
 printf("%lf",s);
   
   
   
 
  return 0;
}
double jc(int x)
{if(x<=1)
  return 1;
 else
  return x*jc(x-1);
  
}





