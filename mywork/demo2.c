/*根据数字输出相应英文的星期

键盘输入一个一位数字，输出该数字对应的星期的英文，如果输入的数字不在1-7范围内，则输出Error。

Tuesday

Wednesday  

Thursday

Friday

Saturday

Sunday

例如 

输入

1

则输出

Monday 


*/

















#include <stdio.h>
int main()
{int a;
    scanf("%d",&a);
    if(a<1||a>7)
printf("error");
else if(a==1)
printf("monday");
else if(a==2)
printf("tuesueday");
else if(a==3)
printf("Wednesday");
else if(a==4)
 printf("Thursday");
else if(a==5)
printf("Friday");
else if(a==6)
printf("Saturday");
else if(a==7)
printf("Sunday");

    return 0;
}
