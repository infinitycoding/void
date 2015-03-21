/*
     Copyright 2015 Infinitycoding all rights reserved
     This file is part of void.

     Void is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.

     Void is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with void. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Michael Sippel <micha@infinitycoding.de>
 */
#include "inode.h"
#include "dir.h"
#include "blockbuffer.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

Inode::Inode()
{
    this->init_buffers(1, 0x1000);
}

Inode::Inode(const char *name_)
    : name(name_)
{
    this->name = NULL;
    this->setName(name_);

    this->parent = NULL;
    this->init_buffers(1, 0x1000);
}

Inode::Inode(const char *name_, DirectoryInode *parent_)
    : name(name_)
{
    this->name = NULL;
    this->setName(name_);

    this->parent = NULL;
    this->setParent(parent_);

    this->init_buffers(1, 0x1000);
}

Inode::~Inode()
{
}

const char *Inode::setName(const char *name_)
{
    this->name = (const char*) realloc((void*) this->name, strlen(name_)+1);
    strcpy((char*) this->name, name_);

    return this->name;
}

void Inode::setParent(DirectoryInode *parent_)
{
    if(this->parent != NULL)
        this->parent->removeEntry(this);

    this->parent = parent_;

    if(this->parent != NULL)
        this->parent->addEntry(this);
}

void Inode::init_buffers(size_t num, size_t size)
{
    this->num_buffers = num;
    this->buffers = (BlockBuffer**) malloc(num * sizeof(BlockBuffer*));
    int i;
    for(i = 0; i < num; i++)
        this->buffers[i] = new BlockBuffer(size);
}

size_t Inode::read(unsigned int buffer, uintptr_t offset, void *data, size_t length)
{
    assert(buffer < num_buffers);
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->read(offset, (uint8_t*) data, length);
    }
    return 0;
}

size_t Inode::write(unsigned int buffer, uintptr_t offset, const void *data, size_t length)
{
    assert(buffer < num_buffers);
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->write(offset, (const uint8_t*) data, length);
    }
    return 0;
}

unsigned int Inode::getID(void)
{
    return this->id;
}

char *Inode::generatePath(void)
{
    return this->generatePath(NULL);
}

char *Inode::generatePath(char *buffer)
{
    size_t length = 0;
    Inode *ino = this;

    while(ino != NULL)
    {
        length += strlen(ino->name) + 1;
        ino = ino->parent;
    }

    if(buffer == NULL)
    {
        buffer = (char*) malloc(length);
    }

    ino = this;
    buffer[length--] = '\0';
    while(ino != NULL)
    {
        int pos = strlen(ino->name) - 1;
        while(pos >= 0)
            buffer[length--] = ino->name[pos--];

        buffer[length--] = '/';
        ino = ino->parent;
    }

    return buffer;
}

