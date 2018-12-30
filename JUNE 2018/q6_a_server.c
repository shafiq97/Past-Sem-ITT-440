/*send 5 random number to client*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h> //srand()
#include <unistd.h> //write()
#include <time.h>

int main()
{
	int s,con,result;
	struct sockaddr_in saddr;

	//create socket
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s < 0)
	{
		perror("Socket problem");
	}

	//define address
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(65456);
	saddr.sin_addr.s_addr = INADDR_ANY;

	//bind with client
	result = bind(s,(struct sockaddr *)&saddr,sizeof(saddr));
	if(result < 0)
	{
		perror("Binding problem");
	}

	//listen maximum of 10
	result = listen(s,10);
	if(result < 0)
	{
		perror("Error listening");
	}

	//accept
	con = accept(s,(struct sockaddr *) NULL,NULL);

	time_t t;
	int num[5];

	//initialize random number generator
	srand((unsigned)time(&t));

	//send 5 number to client
	for(int i=0; i<5; i++)
	{
		num[i] = rand() % 200000; //max of 199999
		if(num[i] < 100000)
		{
			num[i] + 100000 //min of 100000
		}
		write(con,&num[i],sizeof(num[i]));
	}









	return 0;
}