#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char * sstrdup(const char *s)
{
        char *result = (char*)malloc(strlen(s) + 1); //Allocate size+1

        if (result == (char*)0) //Check Null Pointer
                return (char*)0;

        strcpy(result, s); //Copy string into destination
        return result;
}

char *sstrfry(char *s)
{
        int i, j, temp, len = strlen(s);
        int t[len+1];
        static int count=0;
        char *r = (char *)malloc(strlen(s)+1);
        if (r == (char *)0)
                return (char*)0;
        srandom(time(NULL));
        for(i=0; i<len; i++)
        {
begin:
                temp = rand();
                for (j=0 ; j<len; j++)
                        if ((temp % len) == t[j])
                                goto begin;

                t[count]=(temp%len);
                count++;
        }

        for(i=0; i<len;i++)
                printf("t[%d] = %d",i, t[i]);
        for(i=0; i<len;i++)
                r[i] = s[t[i]];

        r[i]='\0';

        return r;
}

