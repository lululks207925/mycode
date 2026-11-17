/*计算逆序数

从键盘输入一个正整数，计算并输出该正整数的逆序数。



所谓逆序数，是指与原数各位上的数字相反的数字，例如 123的逆序数为321。*/
#include <stdio.h>
int main()
{printf("请输入一个正整数");
    int x,t=0;
scanf("%d",&x);

while(x>0)
{
    t=t*10+x%10;
    x=x/10;
}

printf("%d\n",t);

    return 0;
}
