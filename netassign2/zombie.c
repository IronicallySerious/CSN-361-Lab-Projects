#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t c_pid = fork();

	if (c_pid != 0)
	{
		printf("Parent process sleep\n");
		sleep(3);
		printf("Parent process completed\n");
	}
	else
	{
		printf("Child process is now a zombie process\n");
		exit(0);
	}

	return 0;
}
