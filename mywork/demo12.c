/*输入一个非负整数 n，编写程序：
1. 将这个整数逆序输出。
2. 判断这个整数是否为回文数。
3. 如果是回文数，输出 YES，否则输出 NO。*/
#include <stdio.h>
int main()
{printf("请输入一个正整数");
    int x,t=0,p;
scanf("%d",&x);
p=x;
while(x>0)
{
    t=t*10+x%10;
    x=x/10;
}

printf("%d\n",t);
if(t==p)
printf("YES");
else
printf("NO");
  
    return 0;
}