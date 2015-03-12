#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "../src/include/void.h"

struct command_data *cmd;
char *data;
int pid;

int void_open(const char *path, int modus)
{
    cmd->cmd = OPEN;
    cmd->arg_open.modus = modus;
    strcpy(data, path);
    kill(pid, SIGUSR2);
    sleep(1);

    return cmd->ret;
}

int void_close(int fd)
{
    cmd->cmd = CLOSE;
    cmd->arg_close.fd = fd;
    kill(pid, SIGUSR2);
    sleep(1);

    return cmd->ret;
}

int main(int argc, char **argv)
{
    printf("[TEST] Hello!\n");

    pid = fork();
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

        cmd = (struct command_data*) shmat(shm_id, 0, 0);
        data = (char*)cmd + sizeof(struct command_data);

        // register process
        kill(pid, SIGUSR1);
        sleep(1);

        // call something
        int fd = void_open("foo.txt", 0);
        void_close(fd);

        // kill
        printf("[TEST] kill void\n");
        kill(pid, SIGKILL);
    }

    return 0;
}

