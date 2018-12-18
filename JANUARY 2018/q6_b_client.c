#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

int main(int argc, char **argv)
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_STREAM, 0); //socket(domain,type,protocol)

	struct sockaddr_in servaddr; //using struct members in sockaddr_in
	servaddr.sin_family = AF_INET; //tcp ipv4
	servaddr.sin_port=htons(7778); //port number
	servaddr.sin_addr.s_addr = INADDR_ANY; //ip address

	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); //connect(socket,cast address to sockaddr struct,size)	

	time_t current_time; //time declaration
	char* c_time_string; //use to convert to string

	current_time = time(NULL); //get current time

	/* Convert to local time format. */
	c_time_string = ctime(&current_time);

	//printf("Current time is %s", c_time_string);

	write(sockfd,&current_time,sizeof(current_time)); //send current to server in time_t format

	char status[20];

	read(sockfd,&status,sizeof(status));

	printf("%s\n", status);


}	
