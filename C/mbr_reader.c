#include <stdio.h>
#include <fcntl.h>

#define SUCCESS 1
#define ERROR -1

#define BLKSIZE 512
#define PART_OFFSET 446
#define PART_ENTRY_SIZE 16
#define MAX_PART_ENTRY 4

#define MAX_ARG 2

#define PART_ACTIVE 0
#define PART_BHEAD  1
#define PART_BCS0   2
#define PART_BCS1   3
#define PART_ID     4
#define PART_EHEAD  5
#define PART_ECS0   6
#define PART_ECS1   7
#define PART_SS0    8
#define PART_SS1    9
#define PART_SS2   10
#define PART_SS3   11
#define PART_TS0   12
#define PART_TS1   13
#define PART_TS2   14
#define PART_TS3   15

int read_partition(char *file);
int read_partition_info(int *file_ch);
int b2w(int c, int cc);

int active(int part_active);
int start_hcs(int part_h, int part_cs1, int part_cs0);  //c1 c3 c2
int partt(int part_id);
int sectors(int part_ss3, int part_ss2, int part_ss1, int part_ss0);


int main(int argc, char *argv[])
{
        if (argc != MAX_ARG)
        {
                printf("\nUsage: part dump.mbr\n");
                exit(1);
        }

        printf("A H\tC\tS\tID H\tC\tS\tSS\tTS\n");
        if (read_partition(argv[1]) > 0)
                printf("\nRead MBR Successfully\n");
        else
                printf("\nUnable to Read MBR\n");

        return 0;
}

int read_partition(char *file)
{
        FILE *fp;
        int part_bytes[PART_ENTRY_SIZE], i, j;

        fp = fopen (file, "r");
        if (fp > 0)
                fseek(fp, PART_OFFSET, SEEK_SET);
        else
                return ERROR;



        for (j=1; j< MAX_PART_ENTRY ; j++)
        {
                for (i=0; i< PART_ENTRY_SIZE ;i++)
                        part_bytes[i] = fgetc(fp);

                read_partition_info(part_bytes);
        }

        fclose(fp);

        return SUCCESS;

}

int sectors(int part_ss3, int part_ss2, int part_ss1, int part_ss0)
{
        int sectors;
        sectors = (part_ss3<<24) | (part_ss2<<16) | (part_ss1<<8) | (part_ss0);
        printf("%d\t", sectors);

        if (sectors > 0)
                return SUCCESS;
        else
                return ERROR;

}
int read_partition_info(int file_ch[PART_ENTRY_SIZE])
{
        printf("\n");
        if (file_ch[PART_ID] == 0x0)
                exit(1);

        if (active (file_ch[PART_ACTIVE]) < 0)
                printf("Error Reading Active or Not\n");

        if (start_hcs (file_ch[PART_BHEAD], file_ch[PART_BCS1], 
                                                file_ch[PART_BCS0]) < 0)
                printf("Error Reading B HCS\n");

        if (partt(file_ch[PART_ID]) < 0) //Print the Type of Partition
                printf("Error Reading Partition Type\n");

        if (start_hcs (file_ch[PART_EHEAD], file_ch[PART_ECS1], 
                                                file_ch[PART_ECS0]) < 0)
                printf("Error Reading E HCS\n");

        if (sectors(file_ch[PART_SS3], file_ch[PART_SS2], file_ch[PART_SS1], 
                                                file_ch[PART_SS0]) < 0)
                printf("Error Reading Starting Sectors");

        if (sectors(file_ch[PART_TS3], file_ch[PART_TS2], file_ch[PART_TS1], 
                                                file_ch[PART_TS0]) < 0)
                printf("Error Reading Total Sectors");

        return 0;

}

int start_hcs(int part_h, int part_cs1, int part_cs0)
{
        int cs_info; 

        if (part_h >= 0x0)
                printf("%d\t", part_h); //Head
        cs_info = (part_cs1 << 8)| part_cs0;

        printf("%d\t",  //Cylinders
                ((cs_info & 0xFF00) >> 8) | (((cs_info & 0x00FF) & 0xC0) << 2));
        printf("%d\t", (cs_info & 0x3f)); //Sectors
}

int partt(int part_id)
{
        //printf("ch[4] = 0");
        if (part_id == 0x01)
                printf("%x ", part_id);
                //printf("%x 12 bit FAT\n", fst);
        else if (part_id == 0x04)
                printf("%x ", part_id);
                //printf("%x 16 bit FAT < 32MB\n", fst);
        else if (part_id == 0x05)
                printf("%x ", part_id);
                //printf("%x Extended Partition\n", fst);
        else if (part_id == 0x06)
                printf("%x ", part_id);
                //printf("%x 16 bit FAT > 32MB\n", fst);
        else if (part_id == 0x07)
                printf("%x ", part_id);
                //printf(%x NTFS\n", fst);
        else if (part_id == 0x0B)
                printf("%x ", part_id);
                //printf("%x 32 bit FAT upto 2048GB\n", fst);
        else if (part_id == 0x0C)
                printf("%x ", part_id);
                //printf("%x 32 bit FAT  upto 2048GB LBA\n", fst);
        else if (part_id == 0x0E)
                printf("%x ", part_id);
                //printf("%x 16 bit FAT LBA\n", fst);
        else if (part_id == 0x0f)
                printf("%x ", part_id);
                //printf("%x Extended Partition LBA\n", fst);
        else if (part_id == 0x81)
                printf("%x ", part_id);
        else if (part_id == 0x82)
                printf("%x ", part_id);
        else if (part_id == 0x83)
                printf("%x ", part_id);
        else 
                return ERROR; //Error
        return SUCCESS; // Success
}

int active(int part_active)
{

        if (part_active == 0x80)
                printf("* ");
        else if (part_active == 0x0)
                printf("- ");
        else 
                return ERROR;

        return SUCCESS;
}
