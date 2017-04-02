#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bootp.h"
/*Contains Error code for Error*/
#include "err.h"

/*
**************************************************************************
Function: Mapping()
Description:  Random Transmission ID Generation For BOOTP Packet
***************************************************************************
*/
int RndTIDGen()
{
	int i, n;
 	for (i = 0; i< 10; i++)
	{
		n = random();
   		srand(time(NULL));
	}
   	return n;
}

/*
**************************************************************************
Function: Mapping()
Description:  Display Help & Quit
***************************************************************************
*/
void HelpDisp()
{
	printf("\n Usage: Bootpc [options -dhl] [Broadcast Address <optional>]\n");
	printf("\t -d --> Debug Flag \n\t\t This enables the debug printf statements\n");
	printf("\t -l --> Log Flag \n\t\t This enables the log messages to generated\n");
	printf("\t -h --> Help Flag \n\t\t This displays the command help\n");
	printf("\n\t Examples \n\t\t bootpc 192.168.4.255 \n\t\t bootpc \n\t\t"
	       " bootpc -dl 192.168.4.255 \n\t\t bootpc -h \n\t\t bootpc 255.255.255.255\n");
	exit(0);	
}

/*
**************************************************************************
Function: Mapping()
Description: This Function generates IP header checksums
***************************************************************************
*/
unsigned short csum (unsigned short *buf, int nwords)
{
  unsigned long sum;
  for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}

/*
**************************************************************************
Function: Mapping()
Description: This Function Mapps the Structure to the DATAGRAM BUFFER
***************************************************************************
*/
void Mapping()
{
	iph = (struct ip *) datagram;
	udph = (struct udphdr *) (datagram + sizeof (struct ip));
	bootp_req =(struct bootp *) 
			(datagram + sizeof(struct ip) + sizeof(struct udphdr));
	bootp_rep =(struct bootp *)
			(datagram + sizeof(struct ip) + sizeof(struct udphdr));
}

/*
**************************************************************************
Function: Dest_Details()
Description: This Function Checks for Valid BroadCast
***************************************************************************
*/
int ClassType(int type)
{
	if ((type & CLASSA_TYPE) == 0)
       	{
       		// Class A
		return 0;
       	}
        else if ((type & CLASSB_TYPE) == 0)
       	{
       	        // Class B
		return 0;
       	}	
        else if ((type & CLASSC_TYPE) == 0)
       	{
               	// Class C
		return 0;
       	}
	else if (strcmp(dup_badd,BROADCAST) == 0)
	{
		/*Valid BroadCast Address if 255.255.255.255*/
		return 0;
	}
	else 
		return ERRBCAST;
	
}

/*
**************************************************************************
Function: Dest_Details()
Description: This Function Fills in the Destination Details
***************************************************************************
*/
void Dest_Details()
{
	bzero(&their_addr, sizeof(their_addr));	//Zero the Structure

        their_addr.sll_family = AF_PACKET;
	their_addr.sll_protocol = htons(PROTOCOL); //IPv4 = 0x800
        their_addr.sll_ifindex = ifr.ifr_ifindex;
	/*MAC Address setting to ff:ff:ff:ff:ff:ff*/
	their_addr.sll_addr[0] = 0xff;
	their_addr.sll_addr[1] = 0xff;
	their_addr.sll_addr[2] = 0xff;
	their_addr.sll_addr[3] = 0xff;
	their_addr.sll_addr[4] = 0xff;
	their_addr.sll_addr[5] = 0xff;
	their_addr.sll_halen = 6;	//Hw Address Length
}

/*
**************************************************************************
Function: BootpReq_Details()
Description: Fill BOOTP Request Packet
***************************************************************************
*/
void BootpReq_Details()
{
	bzero(bootp_req, sizeof(struct bootp));
	bootp_req->bp_op =  BOOTREQUEST; //1
	bootp_req->bp_htype = ifr.ifr_hwaddr.sa_family;//HTYPE_ETHERNET;
	bootp_req->bp_hlen = HLEN_ETHERNET;
        bootp_req->bp_hops = HOPS;
	bootp_req->bp_xid = RndTIDGen(); //Random Transaction ID Generation
	memcpy(bootp_req->bp_chaddr, ifr.ifr_hwaddr.sa_data, 6);
	
}

/*
**************************************************************************
Function: IP_Details()
Description: Fill IP Packet
***************************************************************************
*/
int IP_Details()
{
	bzero(iph, sizeof(struct ip));

	/*IP Packet Fill*/
	iph->ip_hl 	   = IP_HL;			//IP Header Length 20
  	iph->ip_v 	   = IP_V;			//IP Version
  	iph->ip_tos 	   = IP_TOS;
	
	/* IP Packet Length */
  	iph->ip_len        = htons(sizeof(struct ip) + sizeof(struct udphdr) 
								+ sizeof(struct bootp));
	iph->ip_id 	   = htons (IP_ID);	//ID Doesnot Matter
  	iph->ip_off 	   = IP_OFF;		//Offset
  	iph->ip_ttl 	   = IP_TTL;		//Time to Live
  	iph->ip_p 	   = IP_P;		//Protocol Numer
  	iph->ip_sum 	   = IP_SUM;		//Checksum Intially Zero
  	iph->ip_src.s_addr = IP_SADDR;		//Source IP Address
  	iph->ip_dst.s_addr = IP_DADDR;		//Destination IP Address
	return 0;
}

/*
**************************************************************************
Function: Udp_Details()
Description: Fill UDP Packet
***************************************************************************
*/
int Udp_Details()
{
	bzero(udph, sizeof(struct udphdr));
	udph->source = htons (BP_CLIENT_PORT);	/* BOOTP port */
  	udph->dest   = htons (BP_SERVER_PORT);
	udph->len   = htons(sizeof(struct udphdr) + sizeof(struct bootp));
	return 0;
}

/*
**************************************************************************
Function: Bootp_Reply()
Description: Process BOOTP Reply Packet
***************************************************************************
*/
int Bootp_Reply()
{
	char tmp_buff[100];

	printf("BOOTP Reply Got\n");
	if (strcmp(bootp_rep->bp_chaddr,ifr.ifr_hwaddr.sa_data) == 0)
	{	
		printf("File is %s\n",bootp_rep->bp_file);
	
		if (mode == 1)
		{
			printf("MAC Address Matches\n");
			printf("IP Address is %s\n", 
			inet_ntoa(bootp_rep->bp_yiaddr));
		}

		/* Creating Buff for /sbin/ifconfig eth0 <ipaddress>*/
		strcpy(tmp_buff, "/sbin/ifconfig ");
		strcat(tmp_buff,DEVICE);
		strcat(tmp_buff, " ");
		strcat(tmp_buff, inet_ntoa(bootp_rep->bp_yiaddr));
	
		if (mode == 1)
			printf("Temp Buf = %s\n",tmp_buff);

		/*Set the IP Address*/
		system(tmp_buff);
				
		/*Get the IP Address of the Systen*/
		if( ioctl(sockfd, SIOCGIFADDR, &ifr ) == -1 )
 		{
			if (mode == 1)
			printf("Cannot obtain IP address\n");
			perror("ioctl");
			return ERRGIP;
 		}
		else
		{
			addr = (struct sockaddr_in *)&(ifr.ifr_addr);			
			printf("Current IP Address is %s\n",inet_ntoa(addr->sin_addr));
			return 0;
		}
	}	
	else
	{
		printf("MAC Failed");
		return ERRMAC;
	}
	
	
}
  	
