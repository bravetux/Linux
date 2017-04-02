/*Head Tool*/
#include <stdio.h>

int main(int argc, char * argv[])
{
        FILE *fd;
        int count = 0;
        char c;

        if (argc != 2)
        {
                printf("Usage wcount <filename>\n");
                exit(1);
        }
        fd = fopen(argv[1], "r");
        if (fd < 0)
        {
                printf("\nError Opening File\n");
                exit(1);
        }
        while ((c = fgetc(fd)) != EOF)
        {
          if (c == '\n')
                count++;
        }
        printf("\nLine Count = %d\n", count);
        fseek(fd,0,SEEK_SET);
        count = 10;
        while (count > 0)
        {
                c = fgetc(fd);
                printf("%c",c);
                if (c == '\n')
                {
                        count--;
                }
        }
}
