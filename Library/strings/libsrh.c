#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void sstrcat(char *s, char *t) //String Concatenation
{
        int i, j;
        i = j = 0;
        while (s[i] != '\0') /* find end of s */
        i++;
        while ((s[i++] = t[j++]) != '\0'); /* copy t */

}

size_t sstrspn(const char *patt, const char *stri) //Pattern in String
{
        int c=0, len, i;
        len = strlen(patt);
        while(len--)
        {
                for(i=0; i<strlen(stri); i++)
                        if (*patt == stri[i])
                                c++;
                patt++;

        }
        return c;
}

size_t sstrcspn(const char *patt, const char *stri) //Pattern not in String
{
        int i, len = strlen(patt);
        i = sstrspn(patt,stri);

        return len-i;
}

char *sstrncat(char *s, char *t, int n) //String Concatenation
{
        int i, j;
        i = j = 0;
        while (s[i] != '\0') /* find end of s */
                i++;
        while ((s[i++] = t[j++]) != '\0') /* copy t */
                if (j > n)
                        return s;
	return NULL;
}


char *sstrstr(const char *s, const char *t)
{
        int ls, lt, i=0, j=0;
        int temp;

        ls = strlen(s);
        lt = strlen(t);

        for(j=0; j<ls; j++) //Goto First Char match
                if (s[j] == t[0])
                        break;
        temp =j;                //Store the Match index

        for (i = 0; i<lt; i++,j++) //Check from Index till Pattern length
                if (s[j] != t[i])
                        return NULL;
        return (char *)s+temp;  //Return String From Match Index
}

char *sstrchr(const char *s, char t) //match pattern t in s
{
        int ls, j=0;

        ls = strlen(s);

        for(j=0; j<ls; j++) //Goto First Char match
                if (s[j] == t)
                        return (char *)s+j;     //Return String From Match Index
        return NULL;
}

char *sstrrchr(const char *s, int t) //match pattern t in s from the last
{
        int ls, j=0;

        ls = strlen(s);

        for(j=ls; j>0; j--) //Goto First Char match
                if (s[j] == t)
                        return (char *)s+j;     //Return String From Match Index
	return NULL;
}

char *sstrpbrk(const char *s1, const char *s2)
{
        const char *c = s2;
        if (!*s1)
                return (char *) NULL;
        while (*s1)
        {
                for (c = s2; *c; c++)
                {
                        if (*s1 == *c)
                        break;
                }
                if (*c)
                        break;
                s1++;
        }
        if (*c == '\0')
                s1 = NULL;

        return (char *) s1;
}


