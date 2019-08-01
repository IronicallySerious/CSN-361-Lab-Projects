#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(void)
{
	int child1, child2;
	int i;
	child1 = fork();
	if (child1 == 0)
	{
		int child11 = fork();
		if (child11 == 0)
		{
			sleep(3);
			printf("This is a child11 process and pid is %d, %d\n", getpid(), getppid());
			exit(0);
		}
		else
		{
			int child12 = fork();
			if (child12 == 0)
			{
				sleep(3);
				printf("This is a child12 process and pid is, %d, %d\n", getpid(), getppid());
				exit(0);
			}
		}
		sleep(2);
		printf("This is a child1 process and pid is %d, %d\n", getpid(), getppid());
		exit(0);
	}
	else
	{
		child2 = fork();
		if (child2 == 0)
		{
			int child21 = fork();
			if (child21 == 0)
			{
				sleep(3);
				printf("This is a child21 process and pid is %d, %d\n", getpid(), getppid());
				exit(0);
			}
			else
			{
				int child22 = fork();
				if (child22 == 0)
				{
					sleep(3);
					printf("This is a child22 process and pid is %d, %d\n", getpid(), getppid());
					exit(0);
				}
			}
			sleep(2);
			printf("This is a child2 process and pid is %d, %d\n", getpid(), getppid());
			exit(0);
		}
		sleep(5);
		printf("This is the parent process and pid is %d, %d\n", getpid(), getppid());
	}
}
