int sstrcmp(char *s, char *t);//Compare two strings
int strcmpc(char *s, char *t);//Compare two string ignoring case
int strcmpnc(char *s, char *t, int n); //strcmpc + Compare n characters
int strsize(char *str); //Strlen
int sstrncmp(char *s, char *t, size_t n); //String Cmp atmost n characters
void sstrcat(char *s, char *t); //String Concatenation
size_t sstrcspn(const char *patt, const char *stri); //Patter not in String
size_t sstrspn(const char *patt, const char *stri); //Pattern in String
char *sstrncat(char *s, char *t, int n); //String Concatenation
char *strncpy(char *dest, const char *src, size_t n);//cpy n char from s to d
char *sstrstr(const char *s, const char *t);//locate substring
char *sstrchr(const char *s, char t); //match pattern t in s
char *sstrrchr(const char *s, int t); //match pattern t in s from the last
char *sstrdup(const char *s);//Duplicate a string
char *sstrfry(char *s);//Randomize a string
char *sstrsep(char **stringp, const char *delim);//Extract token from string
char *sstrpbrk(const char *s1, const char *s2); //Search a string for any of a set of chars
char *sstrtok_r (char *s, char *delim, char **save_ptr);//Reentrant Version of strtok
char *sstrtok(char *s, const char *delim);///Extract token from string
