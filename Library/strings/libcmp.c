#include <stdlib.h>
#include <stdio.h>
char *strtok_pos;

int strsize(char *str) //Strlen
{
        int i;

        for (i=0;str[i] != '\0';i++);

        return(i);
}

int sstrcmp(char *s, char *t)//0: equal, <0 S<T, >0 S>T
{
        for(;*s == *t; s++, t++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}

int strcmpc(char *s, char *t) //Strcasecmp
{

        int i, ls, lt, loop;
        ls = strsize(s);
        lt = strsize(t);

        if (ls > lt)
                loop = ls;
        else
                loop = lt;

        for (i=0; i < loop; i++)
        {
                if (s[i] != '\0')
                        s[i]=(s[i] >='A' && s[i] <='Z')?('a' + s[i] -'A'): s[i];
                if (t[i] != '\0')
                        t[i]=(t[i] >='A' && t[i] <='Z')?('a' + t[i] -'A'): t[i];
        }
        return sstrcmp(s, t);
}

int strcmpnc(char *s, char *t, int n) //Compare n characters
{
        char *ss, *tt;

        ss = s;
        tt = t;
        ss[n] = '\0';
        tt[n] = '\0';

        return strcmpc(ss, tt);
}


int sstrncmp(char *s, char *t, size_t n) //String Cmp atmost n characters
{
        for(;*s == *t; s++, t++)
                if (*s == '\0' || --n <= 0)
                        return 0;
        return *s - *t;
}
