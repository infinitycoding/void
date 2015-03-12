
#include "client.h"
#include "filedescriptor.h"
#include "void.h"

#include <stdio.h>

Client::Client(int id_)
    : id(id_)
{
    this->data = (struct command_data*) create_shm(&this->shm_id);
    this->files = new List<FileDescriptor*>();
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

        case READ:
            this->data->ret = read(this->data->arg_read.fd, buffer, this->data->arg_read.length);
            break;

        case WRITE:
            this->data->ret = write(this->data->arg_write.fd, (const void*) buffer, this->data->arg_write.length);
            break;

        default:
            printf("[VOID] undefined command.\n");
            break;
    }
}

FileDescriptor *Client::getDesc(int fd)
{
    ListIterator<FileDescriptor*> it = ListIterator<FileDescriptor*>(this->files);
    while(! it.isLast())
    {
        if(it.getCurrent()->id == fd)
        {
            return it.getCurrent();
        }
        else
        {
            it.next();
        }
    }

    return NULL;
}

int Client::open(const char *path)
{
    printf("[VOID] open \"%s\"\n", path);
    FileDescriptor *desc = new FileDescriptor();
    desc->id = this->files->numOfElements();

    this->files->pushBack(desc);

    return desc->id;
}

int Client::close(int fd)
{
    printf("[VOID] close fd %d\n", fd);

    return 0;
}

int Client::read(int fd, void *buffer, size_t length)
{
    FileDescriptor *desc = this->getDesc(fd);
    printf("[VOID] read %d bytes from %d\n", length, fd);

    return length;
}

int Client::write(int fd, const void *buffer, size_t length)
{
    FileDescriptor *desc = this->getDesc(fd);
    printf("[VOID] write %d bytes to %d\n", length, fd);

    return length;
}

