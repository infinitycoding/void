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
        sleep(1); // wait for init

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
        int fd1 = void_open("foo.txt", 0);
        int fd2 = void_open("bar.bin", 0);

        void_write(fd1, "Hallo Welt!\n", 13);
        void_write(fd2, "Du auch.\n", 10);

        char buf[16];
        void_read(fd1, &buf, 13);
        printf("[TEST] read: %s", buf);

        void_read(fd2, &buf, 10);
        printf("[TEST] read: %s", buf);

        void_close(fd1);
        void_close(fd2);

        // kill
        printf("[TEST] kill void\n");
        kill(pid, SIGKILL);
    }

    return 0;
}

