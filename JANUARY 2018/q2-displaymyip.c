#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) //argument count and argument value
{
	struct hostent *host_info; //struct hostent
	struct in_addr *address; //struct in_addr

	char input[100];

	strcpy(input,argv[1]); //store domain name into input

	host_info = gethostbyname(input); //gethostbyname

	address = (struct in_addr *)(host_info -> h_addr);

	printf("IP Address for domain %s is:\n\t %s \n",input,inet_ntoa(*address));
}