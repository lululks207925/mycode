/*求n，m最大公约数*/
#include <stdio.h>
int main()
{int n,m,r;
    scanf("%d%d",&m,&n);
    r=m%n;
    while(r!=0)
    {m=n;
        n=r;
r=m%n;
    
    }
printf("%d",n);
    



    return 0;
}