#include "inode.h"
#include "blockbuffer.h"

Inode::Inode()
{
    this->buffers[0] = new BlockBuffer(0x1000);
    this->buffers[1] = new BlockBuffer(0x1000);
}

Inode::~Inode()
{
}

int Inode::read(unsigned int buffer, uintptr_t offset, void *data, size_t length)
{
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->read(offset, (uint8_t*) data, length);
    }
    return 0;
}

int Inode::write(unsigned int buffer, uintptr_t offset, const void *data, size_t length)
{
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->write(offset, (const uint8_t*) data, length);
    }
    return 0;
}

