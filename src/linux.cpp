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
}

int init_linux(void)
{
    printf("[VOID] Hello Linux!\n");

    // register signals
    struct sigaction act1, act2;
    sigemptyset(&act1.sa_mask);
    sigemptyset(&act2.sa_mask);
    act1.sa_sigaction = linux_signal_handler;
    act2.sa_sigaction = linux_signal_handler;
    act1.sa_flags = SA_SIGINFO;
    act2.sa_flags = SA_SIGINFO;
    int r1 = sigaction(SIGNAL_REGISTER, &act1, NULL);
    int r2 = sigaction(SIGNAL_COMMAND, &act2, NULL);

    if(r1 == -1 || r2 == -1)
    {
        printf("[VOID] error");
        return -1;
    }

    printf("[VOID] ready.. go sleep\n");

    while(1) pause();

    return 0;
}

void *create_shm(int *shm_id)
{
    *shm_id = shmget(156883, 0x1000, IPC_CREAT | SHM_R | SHM_W);

    if(*shm_id == -1)
    {
        printf("[VOID] error creating shm segment\n");
    }
    else
    {
        void *base = shmat(*shm_id, 0, 0);
        return base;
    }

    return NULL;
}

#endif

