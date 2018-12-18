#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int pfds[2];
	char buf[8] = {""};
	pipe(pfds);
	write(pfds[1], "REMEMBER", 8);
	read(pfds[0],buf, 8);
	printf("so");
	printf("%s\n", buf);
	printf("me;\n");
	printf("I will");
	printf("%s\n", buf);
	printf("you.\n");
	return 0;
}