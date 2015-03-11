#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	printf("[TEST] Hello!\n");

	int pid = fork();
	if(pid == 0)
	{
		printf("[TEST] startig VOID...\n");
		execve("void", NULL, NULL);
	}
	else
	{
		sleep(1);

		kill(pid, SIGUSR1);
		sleep(1);

		kill(pid, SIGUSR2);
		sleep(1);

		kill(pid, SIGKILL);
	}

	return 0;
}

