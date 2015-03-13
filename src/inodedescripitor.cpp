
#include "descriptor.h"
#include "inode.h"

InodeDescriptor::InodeDescriptor(Inode *inode_)
    : inode(inode_)
{
    this->position = 0;
    this->read_buffer = 0;
    this->write_buffer = 0;
}

InodeDescriptor::~InodeDescriptor()
{
}

int InodeDescriptor::read(void *data, size_t length)
{
    return this->inode->read(this->read_buffer, this->position, data, length);
}

int InodeDescriptor::write(const void *data, size_t length)
{
    return this->inode->write(this->write_buffer, this->position, data, length);
}

