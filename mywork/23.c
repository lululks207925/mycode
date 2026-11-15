/*输入一个符合条件的正整数，验证哥德巴赫猜想，输出验证结果。

不考虑输入的合法性。

要求：对程序适当使用自定义函数进行封装

输入：一个大于6的数

输出：

如果满足哥德巴赫猜想，输出 OK，并输出两个素数，前一个小，后一个大

如果不满足哥德巴赫猜想，输出 NO

例如：

输入为

8

输出为

OK 3 5*/
#include<stdio.h>
int ss(int x);
int main()
{int n,i;
int x=2,flag=0;
printf("请输入一个大于6的数");
scanf("%d",&n);
for(i=2;i<n/2;i++)
{
    x++;
if(ss(x)&&ss(n-x))
{flag=1;
printf("YES %d %d",x,n-x);
break;
}
}
if(flag==0)
printf("NO");
return 0;
}

int ss(int x)
{int i;
    if(x<2)
    return 0;
    for (i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;                  /* 有因子立即否掉 */
    return 1;   
}
