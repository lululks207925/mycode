/*2） 设计一个判断素数的函数，在 main() 函数中调用该函数，判断出 100～200 之间的所有素数。*/
#include<stdio.h>
int ss(int x);
int main()
{int n=100;
    for(;n<=200;n++)
    {
        if(ss(n)==1)
printf("%d\n",n);
    }


    return 0;
}
int ss(int x)
{int i,flag;
   for(i=2;i<x/2;i++)
   {flag=1;
    if(x%i==0)
    {flag=0;
    return 0;
    }
   }
if(flag==1)
return 1;

}