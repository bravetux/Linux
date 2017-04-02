/* Copy Program*/
#include <stdio.h>

int main(int argc, char *argv[])
{
        FILE *fd1,*fd2;
        int c;
        if (argc !=3)
        {
                printf("Usage: cp <src file> <dest file>\n");
                exit(1);
        }

        fd1 = fopen(argv[1], "r");
        fd2 = fopen(argv[2], "w");
        while ((c = fgetc(fd1)) != EOF)
        {
                fputc(c,fd2);
        }
        close (fd2);
        close (fd1);
        return 0;
}

