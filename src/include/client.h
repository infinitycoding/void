#ifndef _process_h_
#define _process_h_

#include "void.h"
#include "list.h"
#include "descriptor.h"

class Client
{
    public:
        Client(int id);
        ~Client();

        int id;

        void command(void);

        FileDescriptor *getDesc(int fd);

        int open(const char *path);
        int close(int fd);
        int read(int fd, void *buffer, size_t length);
        int write(int fd, const void *buffer, size_t length);

    private:
        int shm_id;
        struct command_data *data;

        List<FileDescriptor*> *files;
};

#endif

