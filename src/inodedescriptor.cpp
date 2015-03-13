
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

size_t InodeDescriptor::read(void *data, size_t length)
{
    size_t n = this->inode->read(this->read_buffer, this->position, data, length);
    this->position += n;
    return n;
}

size_t InodeDescriptor::write(const void *data, size_t length)
{
    size_t n = this->inode->write(this->write_buffer, this->position, data, length);
    this->position += n;
    return n;
}

