#include <stdio.h>
#include "libvig.h"

#define MAX 30

int main()
{
	char tok[] = "Hello Word- V,ignesh";
	char tok_r[] = "-abc-=-def";
        const char del[] = " -, ";
	char *delim = "-";
       	char *sp; 
	char s1[MAX], s2[MAX];
	size_t nc = 7; //strncmp
	int i, n;

//Strtok
	printf("\nStrtoken ");
	printf("\nTok: %s D: %s \nRes: %s", tok, del,  sstrtok(tok, del));
	printf("\n\nStrtoken_r");
	printf("\nTok: %s D: %s \nRes: %s", tok_r, delim , sstrtok_r(tok_r, delim, &sp));
        printf("\nD: -== R: %s", sstrtok_r(NULL, "-=", &sp)); 
        printf("\nD: = R: %s", sstrtok_r(NULL, "=", &sp));

//Strcat
	printf("\nStrtoken ");
        printf("\nEnter Str1: "); scanf("%s",s1);
        printf("\nEnter Str2: "); scanf("%s",s2);
        sstrcat(s1, s2); printf("\nStrCat: %s",s1);  

//Strncmp
	printf("\nStrncmp");
        printf("\nS1: Hello Ramkumar Match \nS2: Hello, World \n NC %d \nResult: %d", nc, sstrncmp("Hello Ramkumar", "Hello, World", nc));

//Strfry
	printf("\nStrfry \nString %s \nResult: %s", "Hello", sstrfry("Hello"));
//Strstr
	printf("\nS: Hello Ramkumar \nSS:R \nResult: %s",sstrstr("Hello Ramkumar", "R"));
//Strcpy
	printf("\nS: %s", strncpy(s2,s1,2));
//Strcmpc 
	printf("\nEnter Src String: "); scanf("%s", s1);
        printf("\nEnter Target String: "); scanf("%s", s2);
        printf("\nEnter No. of Char: "); scanf("%d", &n);

        i = strcmpc(s1, s2);

        if (i > 0)
                printf("\nSrc > Target\n");
        else if (i < 0)
                printf("\nTarget > Src\n");
        else
                printf("\nSrc = Target \n");
//Strcmpnc
        i = strcmpnc(s1, s2, n);

        if (i == 0)
                printf("\nLength: %d - Char Match\n", n);
        else
                printf("\nLength: %d -  Doesnot Match\n", n);

//Strcspn & strspn

	printf("\nEnter the String: ");
        scanf("%s", s1);
        printf("\nEnter the pattern: ");
        scanf("%s", s2);

        printf("\nMismatch %d", sstrcspn(s2, s1));
        printf("\nMatch %d", sstrspn(s2, s1));

//Strchr
	printf("Result %s", sstrchr("Hello Ramkumar", 'l'));
return 0;
}
