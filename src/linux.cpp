/*
     Copyright 2015 Infinitycoding all rights reserved
     This file is part of void.

     Void is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.

     Void is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with void. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Michael Sippel <micha@infinitycoding.de>
 */
#ifdef __linux__

#include "void.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <linux/wait.h>

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

    kill(pid, SIGCONT);
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

