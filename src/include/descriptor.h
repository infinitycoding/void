#ifndef _descriptor_h_
#define _descriptor_h_

#include "inode.h"

class InodeDescriptor
{
    public:
        InodeDescriptor(Inode *inode_);
        ~InodeDescriptor();

        Inode *inode;
        int position;

        unsigned int read_buffer;
        unsigned int write_buffer;

        int read(void *data, size_t length);
        int write(const void *data, size_t length);
};

class FileDescriptor
{
    public:
        FileDescriptor();
        ~FileDescriptor();

        int id;

        InodeDescriptor *read_descriptor;
        InodeDescriptor *write_descriptor;
};

#endif

