#include <stdio.h>
#include <string.h>

char PreStr[100];
char PostStr[100];
int count;
//优化指出：与其每次传递新的遍历序列， 不如固定初始的两个序列不动，每次传入新的遍历序列索引范围即可
void calc(int a1, int b1, int a2, int b2)
{

    int i;
    if (a1 >= b1)
        return;
    for (i = a2; i <= b2 - 1; i++)
    {
        if (PreStr[a1 + 1] == PostStr[i]) //在后序遍历序列中找到左子树的根节点
            break;
    }

    if (i == b2 - 1)
        count++;

    /*
		Q YUIO PAS
		OIUY ASP Q
    */
    //递归遍历左子树
    calc(a1 + 1, a1 + 1 + (i - a2), a2, i);
    //递归遍历右子树
    calc(a1 + 1 + (i - a2) + 1, b1, i + 1, b2 - 1);
}

int Pow(int n)
{

    int i;
    int m = 1;

    for (i = 0; i < n; i++)
    {
        m *= 2;
    }

    return m;
}

int main()
{
    int Length;
    while (scanf("%s%s", PreStr, PostStr) == 2)
    {
        Length = (int)strlen(PreStr);
        count = 0;
        calc(0, Length - 1, 0, Length - 1);
        printf("%d\n", Pow(count));
    }
    return 0;
}