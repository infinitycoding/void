#ifndef _void_h_
#define _void_h_

#include <sys/types.h>

enum command
{
    OPEN,
    CLOSE,
    READ,
    WRITE
};

struct arg_open
{
    int modus;
};

struct arg_close
{
    int fd;
};

struct arg_read
{
    int fd;
    size_t length;
};

struct arg_write
{
    int fd;
    size_t length;
};

struct command_data
{
    enum command cmd;
    int ret;
    union
    {
        struct arg_open arg_open;
        struct arg_close arg_close;
        struct arg_read arg_read;
        struct arg_write arg_write;
    };
};

void sig_register(int id);
void sig_command(int id);

#ifdef __linux__
int init_linux(void);
#endif

#ifdef __universe__ // ??
int init_universe(void);
#endif


void *create_shm(int *shm_id);

#endif

