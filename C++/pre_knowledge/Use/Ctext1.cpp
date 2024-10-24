# include <stdio.h>
# include <stdlib.h>
int main()
{
    int n;
    int sum=0;
    int ch;
    while(scanf("%d",&n)==1)
    {
        sum += n;
        while((ch=getchar())==' '); //skip space
            if(ch=='\n')
            {
                break;
            }
        ungetc(ch,stdin); 
        // put the number in ch back into the stdin
    }
    printf("%d\n",sum);
    system("pause");
    return 0;
}