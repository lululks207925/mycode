/*计算超级素数



从键盘输入一个大于100的正整数，记作n。

编写程序计算并输出100到n以内的所有超级素数。

所谓超级素数就是一个数本身是素数，从右依次去掉一位数字后所得的数还为素数。例如：239是素数，23是素数，2是素数，那么239就是超级素数。



注意：一行输出一个数。*/
#include <stdio.h>
#include<math.h>
int main()
{int n,x,i,flag;
    scanf("%d",&n);
    for(x=100;x<=n;x++)
    {
    flag=1;
        for(i=2;i<=sqrt(x);i++)
        {
if(x%i==0)
{flag=0;
break;
}
        }
    
if(flag==1)  
printf("%d\n",x);
    }





    

    return 0;
}