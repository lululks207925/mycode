/*编写程序，求s=a+aa+aaa+……+a……a(n个a)之和，并输出，其中a是一个数字，n表示a的位数，a和n由键盘输入。

例如：键盘输入“a=3,n=5”，则表示求 s=3+33+333+3333+33333之和。

输入

a=3,n=5

输出

s=37035*/
#include <stdio.h>
int main()
{int a,n,i;
long long x,sum=0;
    scanf("a=%d,n=%d",&a,&n);
    x=a;
    
for(i=0;i<n;i++)
{sum=sum+x;
    x=x*10+a;
}
printf("s=%lld",sum);
return 0;
}

