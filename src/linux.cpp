#ifdef __linux__

#include <void.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define SIGNAL_REGISTER	SIGUSR1
#define SIGNAL_COMMAND	SIGUSR2

void linux_signal_handler(int sig, siginfo_t *siginfo, void *addr)
{
	pid_t pid = siginfo->si_pid;

	switch(sig)
	{
		case SIGNAL_REGISTER:
			sig_register(pid);
			break;

		case SIGNAL_COMMAND:
			sig_command(pid);
			break;
	};

	pause();
}

int init_linux(void)
{
	printf("[VOID] Hello Linux!\n");

	// register signals
	struct sigaction act;
	act.sa_sigaction = linux_signal_handler;
	act.sa_flags = SA_SIGINFO;

	int r1 = sigaction(SIGNAL_REGISTER, &act, NULL);
	int r2 = sigaction(SIGNAL_COMMAND,  &act, NULL);

	if(r1 == -1 || r2 == -1)
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

	pause();

	return 0;
}

#endif

