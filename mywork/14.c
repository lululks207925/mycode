/*编写程序，输出100～200之间的所有素数，并统计素数的数量。

要求：
1. 使用 for 循环遍历100～200。
2. 使用另一个循环判断当前数字是否为素数。
3. 使用 flag 标记是否为素数。
4. 最后输出素数的总数量。*/
#include<stdio.h>
#include<math.h>
int main()
{int n,t,flag;
    for(n=100;n<=200;n++)
{flag=1;
    for(t=0;n<=sqrt(n);t++)
    {if(n%t!=0)
        flag=0;
        

    }

printf("%f\n",n);

}









return 0;

}