/*一个整数如果按从低位到高位的顺序，奇数位（个位、百位、万位 · · · ）上的数字是奇数，偶数位（十位、千位、十万位 · · · ）上的数字是偶数，我们就称之为“好数”。给定一个正整数 N，请计算从 1 到 N 一共有多少个好数

输入：一个整数 N

输出：一个整数代表答案

输入 24

输出 7*/
#include<stdio.h>
int main()
{int n,i,x,count;
 int s=0,t,flag;
 scanf("%d",&n);
 for(i=1;i<=n;i++)
 {count=0;
   t=i;
  flag=1;
  while(t!=0)
  { 
    count++; 
    x=t%10;
    t=t/10;
    if(count%2==1&&x%2==0)
    {flag=0;
     break;
    }
    if(count%2==0&&x%2==1)
    {flag=0;
     break;
    }
 
  }
 if(flag==1)
   s++;
  
 }
 printf("%d",s);
  return 0;
}