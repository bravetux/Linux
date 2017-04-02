#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
                printf("\n Usage remove <filename>\n");
                exit(1);
        }
        if (remove(argv[1]) < 0)
        {
                printf("\nRemove not Possible\n");
        }
        else
        {
                printf("File Removed\n");
        }
        return 0;
}
