#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid = fork();

	if (pid > 0)
	{
		printf("Child process is now an orphan\n");
	}
	else
	{
		sleep(3);
		printf("Child process terminated\n");
	}

	return 0;
}
