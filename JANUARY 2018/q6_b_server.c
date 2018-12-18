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


int main()
{
	char str[100];
	int listen_fd, comm_fd; //file descriptor to be used


	listen_fd = socket(AF_INET, SOCK_STREAM, 0); /*create a socket AF_INET (IP addressing) and type SOCK_STREAM
												 devices wishing to connect this sokcet will be redirected to listen_fd*/			
	
	struct sockaddr_in servaddr; //struct to hold ip address and port numbers 
	servaddr.sin_family = AF_INET; //set addressing scheme to AF_INET(ip)
	servaddr.sin_port = htons(7778);//listen on port 220000
	servaddr.sin_addr.s_addr = htons(INADDR_ANY); //allow any ip to connect


	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)); //bind

	listen(listen_fd, 10); /*starts listening for connections request waiting,
							if more than 10 the 11th will fail*/

	comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); /*accept a connection from any device willing to connect
																if no one, wait. A new file descriptor will return*/
	bzero( str, 100);//clear str

	time_t current_time; //time declaration

	read(comm_fd,&current_time,sizeof(current_time)); //read in time_t format

	//printf("Current time - %s\n", ctime(&current_time)); //display what it reads in string

    struct tm *hour = localtime(&current_time); //change to struct tm

    int n_hour = hour->tm_hour; //get only hour

    //printf("Hour %i\n", n_hour); 

    char status[20];

    if(n_hour > 0 && n_hour < 12)
    {
    	strcpy(status,"Good Morning");
    }
    else if(n_hour >= 12 && n_hour < 14)
    {
    	strcpy(status,"Good Afternoon");
    }
    else if(n_hour >= 14 && n_hour < 19)
    {
    	strcpy(status,"Good Evening");
    }
    else
    {
    	strcpy(status,"Good Night");
    }

    //printf("Status : %s\n", status);

    write(comm_fd,&status,sizeof(status));
}