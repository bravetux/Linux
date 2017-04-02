/*Binary number is reversed*/
#include <stdio.h>

int main()
{
        int s, d,i;

        printf("Enter the Number: ");
        scanf("%d",&s);
        d=s;
        s=0;
        for (i = 31; i>=0 ; i--)
        {
                s = s | ((d % 2) << i) ;
                d = d/2;
        }
        printf("Binary %x\n", s);

        return 0;
}
