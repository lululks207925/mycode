#include<stdio.h>

int main()
{
    int a=5,b=2,c=0;

    if(a%3==2 && b++>2 || ++c)
        printf("YES ");
    else
        printf("NO ");

    printf("%d %d",b,c);

    return 0;
}