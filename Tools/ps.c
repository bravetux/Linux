#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>


void sdir(char *dirname)
{
        DIR *dir;
        FILE *fp;
        struct dirent *ent;
        struct stat buf;

        char stddir[7]="/proc/";
        char status[8]="/status";
        char path[60];
        char *directory;
        int ch;

        path[0]='\0';
        if ((dir = opendir(dirname)) == NULL)
        {
                perror("Unable to open directory");
                exit(1);
        }

        printf("PID  \tProcess\n");
        printf("---  \t-------\n");
        while ((ent = readdir(dir)) != NULL)
        {
                lstat( ent->d_name, &buf);

                if (S_ISDIR(buf.st_mode))
                {
                        directory = ent->d_name;
                        if (isdigit (directory[0]) > 0)
                        {
                                strcat(path,stddir);
                                strcat(path,directory);
                                strcat(path,status);
                        }
                        else
                                continue;

                        printf("%s \t",directory);
                        if ((fp = fopen(path, "r")) > 0)
                        {
                                fseek(fp, 6, SEEK_SET);
                                while ((ch = getc(fp)) != '\n')
                                {
                                        printf("%c", ch);
                                } 
                                printf("\n");
                        }
                        path[0]='\0';
                }
        }
        if (closedir(dir) != 0)
                perror("Unable to close directory");

}

int main(int argc,char *argv[])
{
  if (argc != 2)
  {
    printf("usage: opendir dirname\n");
    exit(1);
  }
  sdir(argv[1]);
  printf("\n");
  
  return 0;
}

