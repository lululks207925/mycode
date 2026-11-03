/*写出100~200的所有素数*/
#include<stdio.h>
#include<math.h>
int main()
{int n,x,flag;
    for(n=100;n<=200;n++)
{flag=1;
for(x=2;x<=sqrt(n);x++)
{if(n%x==0)
    flag=0;

}


if(flag==1)
printf("%d\n",n);
}



    return 0;
}