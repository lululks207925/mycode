/*写出100~200的所有素数(素数从2开始判断)*/
#include<stdio.h>

int main()
{
    int n,t,flag;

    for(n=100;n<=200;n++)
    {
        flag=1;  // 假设n是素数

        for(t=2;t*t<=n;t++)
        {
            if(n%t==0)
            {
                flag=0;  // 找到因数，不是素数
                break;
            }
        }

        if(flag==1)
            printf("%d\n",n);
    }

    return 0;
}