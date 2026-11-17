/*题目描述
给出 n 和 n 个整数 a 
i
​
 ，求这 n 个整数中最小值是什么。

输入格式
第一行输入一个正整数 n，表示数字个数。

第二行输入 n 个非负整数，表示 a 
1,a 
2…a 
n ，以空格隔开。
输出格式
输出一个非负整数，表示这 n 个非负整数中的最小值。
输入输出样例
输入 #1复制
5
5 7 4 2 6
输出 #1复制
2*/
#include<stdio.h>
# define N 100
int main()
{int n,a,i,x;
    int arr[N];
    scanf("%d",&n);
    for(i=0;i<=n-1;i++)
    {
    scanf("%d",&a);
    arr[i]=a;
}
   
    int min=arr[0];
    for(x=1;x<n;x++)
    {
    
if(min>arr[x])
{
min=arr[x];

}
    }
printf("%d",min);


    return 0;
}