/*判断是否闰年

输入一个整数表示年份，如果是非正整数，输出“Invalid Input”；如果是正整数，判断是否是闰年，如果是输出“YES”，否则输出“NO”。
*/
#include<stdio.h>
int main()
{int x;
  scanf("%d",&x);
  if(x<=0)
    printf("Inaclid Input");
 else if(x%400==0||(x%4==0&&x%100!=0))
 printf("YES");
  else 
printf("NO");
   
 
  
  
  return 0;
}