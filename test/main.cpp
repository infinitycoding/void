#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <linux/wait.h>

#include "../src/include/void.h"

struct command_data *cmd;
void *data;
int pid;

int void_open(const char *path, int modus)
{
    cmd->cmd = OPEN;
    cmd->arg_open.modus = modus;
    strcpy((char*)data, path);
    kill(pid, SIGUSR2);
    raise(SIGSTOP);

    return cmd->ret;
}

int void_close(int fd)
{
    cmd->cmd = CLOSE;
    cmd->arg_close.fd = fd;
    kill(pid, SIGUSR2);
    raise(SIGSTOP);

    return cmd->ret;
}

int void_read(int fd, void *buf, size_t length)
{
    cmd->cmd = READ;
    cmd->arg_read.fd = fd;
    cmd->arg_read.length = length;
    kill(pid, SIGUSR2);
    raise(SIGSTOP);

    int len = cmd->ret;
    memcpy(buf, (const void*)data, len);

    return len;
}

int void_write(int fd, const void *buf, size_t length)
{
    cmd->cmd = WRITE;
    cmd->arg_write.fd = fd;
    cmd->arg_write.length = length;
    memcpy(data, buf, length);
    kill(pid, SIGUSR2);
    raise(SIGSTOP);

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
        sleep(2); // wait for init

        // create shm
        int shm_id = shmget(156883, 0x1000, IPC_CREAT | SHM_R | SHM_W);

        cmd = (struct command_data*) shmat(shm_id, 0, 0);
        data = (char*)cmd + sizeof(struct command_data);

        // register process
        printf("[TEST] register..\n");
        kill(pid, SIGUSR1);
        raise(SIGSTOP);

        // call something
        printf("[TEST] call some stuff..\n");
        int fd = void_open("/hello", 0);

        char buf[64];
        int ret = void_read(fd, &buf, 64);
        printf("[TEST] got %d, buf: %s \n", ret, buf);

        void_close(fd);

        // kill
        printf("[TEST] kill void\n");
        kill(pid, SIGKILL);
    }

    return 0;
}

