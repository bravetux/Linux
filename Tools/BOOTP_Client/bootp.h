#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <syslog.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <errno.h>
#include <error.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <sys/time.h>
#include <math.h>

/* Packet Field Sizes */
#define BP_CHADDR_LEN    16 /*Client Hardware Address*/
#define BP_SNAME_LEN     64 /*Optional Sever Host Name */
#define BP_FILE_LEN     128 /*Boot file name*/
#define BP_VEND_LEN      64 /*Optional Vendor Specific Area*/

/* Port Details */
#define BP_SERVER_PORT   67
#define BP_CLIENT_PORT   68
#define SERVERPORT 67 //4950

/* Opcodes Details */
#define BOOTREPLY        0x2
#define BOOTREQUEST      0x1

/* htype Details from RFC 951 */
#define HTYPE_ETHERNET    0x1
#define HLEN_ETHERNET     0x6

/*Gateway Hops*/
#define HOPS 0x0

/* Product Information */
#define BPCVERSION  "1.0"

/*MAX Bufferlength */
#define MAXBUFLEN 400

/*Device Info*/
#define DEVICE "eth0"

/*Class Types*/
#define CLASSA_TYPE 0x80000000
#define CLASSB_TYPE 0x40000000
#define CLASSC_TYPE 0x20000000
#define BROADC_TYPE 0xFF000000

#define MASK_A 0xFF000000
#define MASK_B 0xFFFF0000
#define MASK_C 0xFFFFFF00
	
#define BROADCAST "255.255.255.255"

/*IP Packet Details*/
#undef IP_TTL
#undef IP_TOS

#define IP_HL    5		//IP Header Length 20
#define IP_V     4		//IP Version
#define IP_TOS   0
#define IP_ID    54321		//ID Doesnot Matter
#define IP_OFF   0		//Offset
#define IP_TTL   64     	//Time to Live
#define IP_P     17		//UDP Protocol Numer
#define IP_SUM   0		//Checksum Intially Zero
#define IP_SADDR 0		//Source IP Address
#define IP_DADDR 0xffffffff	//Destination IP Address

/*Protocol Number*/
#define PROTOCOL 0x800

/*Datagram Size*/
#define DGRAM_BUFF 500

/*UDP Checksum*/
typedef unsigned short u16;
typedef unsigned long u32;

struct bootp
{
	char    bp_op;                     /* 1 packet opcode type */
    	char    bp_htype;                  /* 1 hardware addr type */
    	char    bp_hlen;                   /* 1 hardware addr length */
    	char    bp_hops;                   /* 1 gateway hops */
    	unsigned int     bp_xid;           /* 4 transaction ID */
	unsigned short   bp_secs;          /* 2 seconds since boot began */
    	unsigned short   bp_unused;        /* 2 unsused*/
    	struct in_addr   bp_ciaddr;        /* 4 client IP address */
	struct in_addr   bp_yiaddr;        /* 4 'your' IP address */
    	struct in_addr   bp_siaddr;        /* 4 server IP address */
    	struct in_addr   bp_giaddr;        /* 4 gateway IP address */
    	char    bp_chaddr[BP_CHADDR_LEN];  /* 16 client hardware address */
    	char    bp_sname[BP_SNAME_LEN];    /* 64 server host name */
    	char    bp_file[BP_FILE_LEN];      /* 128 boot file name */
    	char    bp_vend[BP_VEND_LEN];      /* 64 vendor-specific area */
} __attribute__((packed));



struct ifreq ifr;  		//Interface Request Structure used for socket ioctls

struct bootp *bootp_req; 	//BOOTP Request
struct bootp *bootp_rep;	//BOOTP Reply

struct sockaddr_in temp_addr; 	//Temporary Address information
struct sockaddr_in* addr;
struct sockaddr_ll their_addr; 	// connector's address information
struct hostent *he;		//Host Entry Information

struct timeval wait;		//For Select Operation
struct ip *iph;			//IP Packet
struct udphdr *udph;		//UDP Packet


char datagram [DGRAM_BUFF];	//Buffer For Sending & Recieving
char dup_badd [BP_CHADDR_LEN];	//Duplicate BroadCast Address
int sockfd;			//Socket For Communication

int mode;
int lmode;


