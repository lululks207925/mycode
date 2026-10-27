/*判断一元二次方程是否有解，并计算。

对于一个一元二次方程 ax^2+bx+c=0，从键盘输入a，b和c的值，计算方程在实数域的解。

 如果没有解，输出“没有解”；如果有解，直接输出解。



注意：

输入时，一行输入一个数；

输出时，一行输出一个数，按照从小到大的顺序输出；

符号^表示乘方。*/

#include <stdio.h>
#include <math.h>

int main()
{
    double a,b,c,x1,x2,h;

    scanf("%lf%lf%lf",&a,&b,&c);

    h=b*b-4*a*c;

    if(h<0)
    {
        printf("没有解");
    }
    else
    {
        x1=(-b+sqrt(h))/(2*a);
        x2=(-b-sqrt(h))/(2*a);

        if(x1>x2)
            printf("%f\n%f\n",x2,x1);
        else if(x1<x2)
            printf("%f\n%f\n",x1,x2);
        else
            printf("%f\n",x1);
    }

    return 0;
}
