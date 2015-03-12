#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../src/include/void.h"

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
		sleep(1); // wait for init

		// create shm
		int shm_id = shmget(156883, 0x1000, IPC_CREAT | SHM_R | SHM_W);

		struct command_data *cmd = (struct command_data*) shmat(shm_id, 0, 0);
		char *data = (char*)cmd + sizeof(struct command_data);

		// register process
		kill(pid, SIGUSR1);
		sleep(1);

		// call something
		cmd->cmd = OPEN;
		strcpy(data, "foo.txt");
		kill(pid, SIGUSR2);
		sleep(1);

		// kill
		printf("[TEST] kill void\n");
		kill(pid, SIGKILL);
	}

	return 0;
}

