/*Char to Int conversion*/
#include <stdio.h>

int ai(char ss[]);

int main()
{
        char ss[]="1234";
        printf("Number: %d", ai(ss));
}

int ai(char ss[])
{
        int i, n=0;
        for(i = 0; ss[i] >= '0' && ss[i] <= '9'; i++)
                n = (n * 10) + (ss[i] - '0');
        return n;
}

