#include <stdio.h>
#include <string.h>

void ia(int no);

int main()
{
        ia(-365);
        return 0;
}

void ia(int no)
{
        int i=0, cno=0, t, j=0;
        char ss[10], tss[10];

        if (no < 0)
        {
                cno = no; 
                no *= (-1);
        }

        do
        {
                ss[i++] = (no % 10) + '0'; 

        }while ( (no /= 10) > 0);

        if (cno < 0) 
                ss[i++] = '-';

        ss[i] = '\0';

        for ( i=strlen(ss)-1,j=0; i>=0; i--,j++)
        {
                tss[i]= ss[j];
                printf("Tss[%d] = %c\n", i, tss[i]);
        }

        tss[j] = '\0';

        printf("The String is %s\n", tss);
}
