/*计算完数

求出1000以内的所有完数，所谓完数是与其所有因子之和相等的数。

例如 6，因子之和为1+2+3



输出形式：

6=1+2+3

28=1+2+4+7+14

496=1+2+4+8+16+31+62+124+248*/
#include<stdio.h>
int main()
{int n=1000,x,i;
    int sum,count;
    for(x=2;x<=1000;x++)
    {sum=0;
    
    for(i=1;i<x;i++)
    {if(x%i==0)
        {sum=sum+i;
        }
    }
        if(sum==x)
        {count=0;
            printf("%d=",x);
            for(i=1;i<x;i++)
            {
            
                if(x%i==0)
                {if(count>0)
printf("+");
printf("%d",i);
count++;
                }
            }


printf("\n");
        }

    }
    

    return 0;
}