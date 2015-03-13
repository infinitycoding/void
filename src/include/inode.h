
#ifndef _inode_h_
#define _inode_h_

#include "blockbuffer.h"

class Inode
{
    public:
        Inode();
        ~Inode();

        char *name;
        size_t length;
        Inode *parent;

        BlockBuffer *buffers[2];

        int read(unsigned int buffer, uintptr_t offset, void *data, size_t length);
        int write(unsigned int buffer, uintptr_t offset, const void *data, size_t length);
};

#endif

