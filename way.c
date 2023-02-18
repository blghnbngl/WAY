/***********************************************************
* WAY
***********************************************************/

#include<stdio.h> 
#include<sys/utsname.h> 
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <net/ethernet.h> /* the L2 protocols */


int main()
{

	//For system info
	struct utsname uname_pointer;	
	int result = 0; //A variable to check results
	
	//For network interfaces
	struct ifaddrs *ifaddr=NULL;
	struct ifaddrs *ifa = NULL;
	int family, s, I = 0;
	char networkHost[NI_MAXHOST];


	//Step 1, get os info
	printf("1) System information\n");

	result = uname(&uname_pointer); 

	if(result != 0)	
	{
		perror("uname doesn't return 0, so there is an error with system info\n");
		printf("uname doesn't return 0, so there is an error with system info with no: %d \n", result);
		return(result);
	}
	else	//Print the information
	{	
		printf("System name - %s \n", uname_pointer.sysname);
		printf("Nodename    - %s \n", uname_pointer.nodename);
		printf("Release     - %s \n", uname_pointer.release);
		printf("Version     - %s \n", uname_pointer.version);
		printf("Machine     - %s \n", uname_pointer.machine);
	}

	result = getifaddrs(&ifaddr);

	//Step 2, get network info
	printf("\n2) Network interfaces\n");
	if(result != 0)
	{
		perror("getifaddrs fails, there is an error with network info\n");
		printf("getifaddrs fails, there is an error with network info\n");
	}
	else
	{
		for(ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
		{
			if (ifa->ifa_addr == NULL)
				continue;

			family = ifa->ifa_addr->sa_family;

			/* Display interface name and family (including symbolic form of the latter for the common families) */

			printf("%s  address family: %d %s\n", ifa->ifa_name, family,
				//(family == AF_PACKET) ? " (AF_PACKET)" :
				(family == AF_INET) ?   " (AF_INET)" :
				(family == AF_INET6) ?  " (AF_INET6)" : "not IPv4 or IPv6");

			/* For an AF_INET* interface address, display the address */

			if (family == AF_INET || family == AF_INET6) 
			{
				s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) :
					sizeof(struct sockaddr_in6), networkHost, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
				if (s!= 0) 
				{
					printf("getnameinfo() for network interface failed: %s\n", gai_strerror(s));
            				perror("getnameinfo() for network interface failed \n");
				}
				else
					printf("\taddress: <%s>\n", networkHost);
         		}
			/* Bilgehan: New addition

			else if (family == AF_PACKET && ifa->ifa_data != NULL) {
	                   struct rtnl_link_stats *stats = ifa->ifa_data;	
        	           printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                          "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                          stats->tx_packets, stats->rx_packets,
                          stats->tx_bytes, stats->rx_bytes);
               }*/
		}
        	freeifaddrs(ifaddr);
    	}

	return(result);
}

