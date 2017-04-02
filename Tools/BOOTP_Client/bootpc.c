/* Contains Definitions & BOOTP Structure */
#include "bootp.h" 
/*Contains Error code for Error*/
#include "err.h"
/*Contains Function Prototypes*/
#include "libbootp.h"

fd_set read_template;
unsigned int ips,udps;

int main(int argc, char *argv[])
{
        
     	socklen_t addr_len, len;	 
	static int retries=0;
	int type; //Class Type
	char udpcs[20];
	char badd_temp[16], *add_temp, *x[3];
	unsigned char *hwaddr;
	unsigned short udpchecksum;
	int i , ret, retval, iplen, udplen, numbytes;
	//Intializations
	int broadcast = 1, flag = 0;
	
	memset(datagram,0, DGRAM_BUFF);
	memset(&ifr, 0, sizeof(ifr));

	openlog ("bootpc", LOG_NDELAY, LOG_LOCAL0);		
	Mapping();

	if (argc == 1)
	{
		goto M;
	}
		
	if (strchr(argv[1], '-') != NULL)
       	{
               	if (strchr(argv[1], 'h') != NULL)
		{
			HelpDisp();
		}
               	else if (strchr(argv[1], 'l') != NULL)
		{
			lmode = 2;
		}
               	if (strchr(argv[1], 'd') != NULL)
		{
			if (lmode == 2)
				syslog(LOG_LOCAL0|LOG_DEBUG,"Debug Enabled");
			mode = 1;
		}	
	}
	else if ( (strchr(argv[1], '.') != NULL) )
	{

		strcpy(badd_temp, argv[1]);
		strcpy(dup_badd, argv[1]);
        	temp_addr.sin_addr.s_addr = atol(argv[1]); //MAC Address Storing
		flag = 1;
		goto L;
	}

	if (argc == 3)
	{
		if ( (strchr(argv[2], '.') != NULL) )
		{
			strcpy(badd_temp,argv[2]);
			strcpy(dup_badd, argv[2]);
        		temp_addr.sin_addr.s_addr = atol(argv[2]); //MAC Address Storing
			flag = 1;
			goto L;
		}
	}
M:
	if ((argc == 1) || (argc == 2))
	{
		strcpy(badd_temp, BROADCAST);
		strcpy(dup_badd, BROADCAST);	
        	temp_addr.sin_addr.s_addr = atol(BROADCAST); //MAC Address Storing
		flag = 1;
	}
L:
	if (flag == 1)
	{
		x[0] = strtok_r(badd_temp,".", &add_temp);
		x[1] = strtok_r(NULL,".", &add_temp);
		x[2] = strtok_r(NULL,".", &add_temp);
		x[3] = strtok_r(NULL,".", &add_temp);

		if (strcmp(x[3],"255") != NULL)
		{
			return ERRBCAST;
		}
	
        	type = ntohl(temp_addr.sin_addr.s_addr);

		if (ClassType(type) < 0)
			return ERRBCAST;
		else if (mode == 1)
			printf("Broadcast Address is Valid\n");
			
	}

	if ((sockfd = socket(PF_PACKET,SOCK_DGRAM,htons(PROTOCOL))) == -1) 
	{
		perror("socket");
		return ERRSOCK;
	}

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Socket Created");

	if (mode == 1)
		printf("Socket Created\n");

	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, 
							sizeof(broadcast)) == -1) 
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"setsockopt for Broadcast Error");

                perror("setsockopt (SO_BROADCAST)");
		return ERRSOCKOPT;
        }

	if (setsockopt(sockfd, SOL_SOCKET, SO_NO_CHECK, &broadcast, sizeof(broadcast)) == -1)
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"setsockopt for no checksum Error");

		perror("setsockopt (SO_BROADCAST)");
		return ERRSOCKOPT;
	}

	if (mode == 1)
		printf("Broadcast Option Set\n");

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Broadcast Option Set");

	memcpy(ifr.ifr_name, DEVICE, strlen(DEVICE)+1);

	if (ioctl(sockfd, SIOCGIFINDEX, &ifr) < 0) //Obtain the Index
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"Error retrieving index");

                perror("Error retrieving index\n");
		return ERRIOCTLI;
        }

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Index Value Recieved using IOCTL");

	if (mode == 1)
		printf("Index Value Recieved using IOCTL\n");
	
	Dest_Details();

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Destination Details Filled");

	if (mode == 1)
		printf("Destination Details Filled\n");
	
	if (bind(sockfd, (struct sockaddr *)&their_addr, sizeof(their_addr)) == -1)
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"Error binding socket");

		perror("Error binding socket\n");
		return ERRBIND;
	}

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Socket Binding Completed");

	if (mode == 1)
		printf("Socket Binding Completed\n");

	/*Obtain MAC Address for device:eth0*/
 	memcpy(ifr.ifr_name, DEVICE, strlen(DEVICE)+1);
 	if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0) 
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"Error retrieving mac address");
		perror("Error retrieving mac address");
		return ERRIOCTLM;
	}

	if (lmode == 2)
	{
			syslog(LOG_LOCAL0|LOG_DEBUG,"MAC Address Recieved using IOCTL");
			syslog(LOG_LOCAL0|LOG_DEBUG,"Filling the BOOTP REQUEST PACKET");
	}

	if (mode == 1)
	{
		printf("MAC Address Recieved using IOCTL\n");
		printf("Filling the BOOTP REQUEST PACKET\n");
	}
A:
	BootpReq_Details();

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Message: BOOTP Request Packet Created");
		
	if (mode == 1)
	{
		printf("Message: BOOTP Request Packet Created");
		printf("\nSize of IP %d", sizeof(struct ip));
		printf("\nSize of UDP %d", sizeof(struct udphdr)); 
		printf("\nSize of BOOTP %d\n", sizeof(struct bootp));
	}
	
	IP_Details();

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"IP Packet Created");

	if (mode == 1)
		printf("IP Packet Created\n");

	iplen = ntohs(iph->ip_len);
	
	/*UDP Packet Fill*/
	Udp_Details();
	
	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"UDP Packet Created");
	
	if (mode == 1)
		printf("UDP Packet Created\n");

	udplen = ntohs(udph->len);

	if (mode == 1)
	{
		printf("UDP LEN = %d \n IP_LEN = %d \n ", udplen, iplen);
		printf("Creating Check sums\n");
	}

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Creating Check sums");
			
	udph->check = csum((unsigned short *) (datagram + 20), udplen >> 1); 
	iph->ip_sum = csum ((unsigned short *) datagram, iplen  >> 1); 
	udph->check = 0x0;

	if (mode == 1)
	{	
		printf("MAC ADDRESS\n");
		hwaddr = (unsigned char *)ifr.ifr_hwaddr.sa_data;

		printf("The result of SIOCGIFHWADDR is type %d  "
		   "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x.\n",
		   ifr.ifr_hwaddr.sa_family, hwaddr[0], hwaddr[1],
		   hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
	}

	wait.tv_sec = 0;

	if ((numbytes=sendto(sockfd, datagram ,iplen, 0,
		(struct sockaddr *)&their_addr, sizeof(struct sockaddr_ll))) == -1) 
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"Sendto error");
		perror("sendto");
		return ERRSENDTO;
	}
	
	if (mode == 1)
		printf("sent %d bytes broadcasted\n", numbytes);

	if (lmode == 2)
		syslog(LOG_LOCAL0|LOG_DEBUG,"Packet broadcasted");

	wait.tv_sec = pow(2,retries);
        
	FD_ZERO(&read_template);
	FD_SET(sockfd, &read_template);
	len = sizeof(struct sockaddr_ll);

	retval = select(sockfd+1, &read_template, NULL, NULL, &wait);

	if (retval > 0) 
	{
		if ((numbytes = recvfrom(sockfd, datagram, sizeof(datagram), 0 , 
			(struct sockaddr_ll *)&their_addr, &len)) == -1)
		{
				if (lmode == 2)
					syslog(LOG_LOCAL0|LOG_DEBUG,"recvfrom error");
				perror("recvfrom");
				return ERRRCVFROM;
		}
	}
	
	if((bootp_rep->bp_op == BOOTREPLY) 
		&& (bootp_rep->bp_hlen == HLEN_ETHERNET) 
		&& (ntohs(udph->len) == udplen) 
		&& (ntohs(udph->source) == BP_SERVER_PORT)
		&& (ntohs(udph->dest) == BP_CLIENT_PORT) ) 

	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"Revcieved Packet");
		
		if (mode == 1)
			printf("Recieved %d bytes broadcasted\n", numbytes);

		Bootp_Reply();	
	}
	else if (retries <= 10)
	{	
		retries++;
		goto A;
	}
	else if (retries >= 10)
	{
		retries = 1;
		goto A;
	}
	else
	{
		if (lmode == 2)
			syslog(LOG_LOCAL0|LOG_DEBUG,"TIMED OUT...");
		printf("Timed Out...\n");
		return TIMEOUT;
	}
	
        close(sockfd);
        return 0;
}
