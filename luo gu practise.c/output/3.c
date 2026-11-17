/*用高精度计算出 S=1!+2!+3!+⋯+n!（n≤50）。

其中 ! 表示阶乘，定义为 n!=n×(n−1)×(n−2)×⋯×1。例如，5!=5×4×3×2×1=120。

输入格式
一个正整数 n。

输出格式
一个正整数 S，表示计算结果。

输入输出样例*/
#include<stdio.h>
int jc(int x);
int main()
{int n,s=0,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
s=s+jc(i);

    }
printf("%d",s);




    return 0;
}
int jc(int x)
{if(x<=1)
    return 1;
    else
    return x*jc(x-1);
}