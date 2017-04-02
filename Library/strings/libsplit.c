#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
char *strtok_pos;

char *sstrsep(char **stringp, const char *delim)
{
        char *res;
        if (!stringp || !*stringp || !**stringp)
                return (char*)0;

        res = *stringp;
        while(**stringp && !strchr(delim, **stringp))
                ++(*stringp);

        if (**stringp)
        {
                **stringp = '\0';
                ++(*stringp);
        }

        return res;
}


char *sstrtok_r (char *s, char *delim, char **save_ptr)
{
        char *token;

        if (s == NULL)
                s = *save_ptr;

        /* Scan leading delimiters.  */
        s += strspn (s, delim); //Shifting s past delimiters
        if (*s == '\0')
        {
                *save_ptr = s;
                return NULL;
        }

        /* Find the end of the token.  */
        token = s;
        s = strpbrk (token, delim); //Shifts to the next token

        if (s == NULL)  /* This token finishes the string.  */
        {
                *save_ptr = token + strlen (token);
        }
        else
        {
                /* Terminate the token and make *SAVE_PTR point past it.  */
                *s = '\0';
                *save_ptr = s + 1;
        }

        return token;
}

char *sstrtok(char *s, const char *delim)
{
        while (s != '\0')
                return strtok_r(s,delim,&strtok_pos);
	return NULL;
}


