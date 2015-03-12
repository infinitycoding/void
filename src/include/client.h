#ifndef _process_h_
#define _process_h_

#include <void.h>


class Client
{
public:
    Client(int id);
    ~Client();

    int id;

    void command(void);

    int open(const char *path);
    int close(int fd);
    int read(void);
    int write(void);

private:
    int shm_id;
    struct command_data *data;
};

#endif

