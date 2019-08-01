#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void check_host_name(int hostname)
{
	if (hostname == -1)
	{
		perror("gethostname");
		exit(1);
	}
}
void check_host_entry(struct hostent *hostentry)
{
	if (hostentry == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
}
void IP_formatter(char *IPbuffer)
{
	if (NULL == IPbuffer)
	{
		perror("inet_ntoa");
		exit(1);
	}
}

void main()
{
	char host[256];
	char *IP;
	struct hostent *host_entry;
	int hostname;
	//find the host name
	hostname = gethostname(host, sizeof(host));
	check_host_name(hostname);
	//find host information
	host_entry = gethostbyname(host);
	check_host_entry(host_entry);
	//Convert into IP string
	IP = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
	printf("Current Host Name: %s\n", host);
	printf("Host IP: %s\n", IP);
}
