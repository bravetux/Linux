#include <stdio.h>

#define LAST 10

int main(int argc, char *argv[])
{
        int ch, line=0, count=0;
        FILE *fp;

        if (argc != 2)
        {
                printf("Usage Tail <filename>\n");
                exit(1);
        }

        fp = fopen(argv[1],"r");

        if (fp == NULL)
                exit(1);

        while ((ch = getc(fp)) != EOF)
        {
                if (ch == '\n')
                        line++;
        }

        fseek(fp, SEEK_SET, 0); //Begining of file

        while ((ch = getc(fp)) != EOF)
        {
                if (ch == '\n')
                        count++;
                if (count == (line - LAST))
                        break;
        }

        while ((ch = getc(fp)) != EOF)
        {
                printf("%c", ch);
        }

        fclose(fp);
        return 0;
}
