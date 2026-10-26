#include <stdio.h>
int main()
{
int x;
scanf("%d",&x);
if(x>=90)
{
printf("优秀");
}
else if(x>=60&&x<90)
{
	printf("及格");
}
else 
{
printf("不及格");
}


return 0;
}