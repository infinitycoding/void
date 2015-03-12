
#include "client.h"
#include "filedescriptor.h"
#include "void.h"

#include <stdio.h>

Client::Client(int id_)
    : id(id_)
{
    this->data = (struct command_data*) create_shm(&this->shm_id);
}

Client::~Client()
{
}

void Client::command(void)
{
    void *buffer = (void*) this->data + sizeof(struct command_data);

    switch(this->data->cmd)
    {
        case OPEN:
            this->data->ret = open((const char*) buffer);
            break;

        case CLOSE:
            this->data->ret = close(this->data->arg_close.fd);
            break;

        default:
            printf("[VOID] undefined command.\n");
            break;
    }
}

int Client::open(const char *path)
{
    printf("[VOID] open \"%s\"\n", path);
    FileDescriptor *desc = new FileDescriptor();
    desc->id = 0;

    return desc->id;
}

int Client::close(int fd)
{
    printf("[VOID] close fd %d\n", fd);
    return 0;
}

