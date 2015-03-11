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

		printf("[TEST] testpid: %d, voidpid: %d\n", getpid(), pid);
		printf("[TEST] send signal SIGUSR1 (%d)\n", SIGUSR1);
		kill(pid, SIGUSR1);

		int status;
		waitpid(pid, &status, 0);

		printf("void terminated with %d\n", status);
	}

	return 0;
}

