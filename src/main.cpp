#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void register_process(int sig, siginfo_t *siginfo, void *addr)
{
	pid_t pid = siginfo->si_pid;
	printf("[VOID] got request from pid %d\n", pid);


	printf("[VOID] terminating..\n");
	exit(0);
}

int main(int argc, char **argv)
{
	printf("[VOID] Hello Universe!\n");

	struct sigaction act;
	act.sa_sigaction = register_process;
	act.sa_flags = SA_SIGINFO;

	if( sigaction(SIGUSR1, &act, NULL) == -1)
	{
		printf("[VOID] error");
		return -1;
	}

	// create public shm segment
	int shm_id = shmget(IPC_PRIVATE, 0x1000, IPC_CREAT | SHM_R | SHM_W);

	if(shm_id == -1)
	{
		printf("[VOID] error creating shm segment\n");
	}
	else
	{
		void *base = shmat(shm_id, 0, 0);
		printf("[VOID] shm at adress 0x%x\n", base);
	}

	while(1);

	return 0;
}

