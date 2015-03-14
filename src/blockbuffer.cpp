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
#include "blockbuffer.h"
#include "list.h"

#include <stdlib.h>

BlockBuffer::BlockBuffer(size_t block_size_)
    : block_size(block_size_)
{
    this->blocks = new List<struct buffer_block>();
}

BlockBuffer::~BlockBuffer()
{
}

uint8_t *BlockBuffer::getBlock(unsigned int id)
{
    ListIterator<struct buffer_block> it = ListIterator<struct buffer_block>(this->blocks);

    while(! it.isLast())
    {
        if(it.getCurrent().id == id)
            return it.getCurrent().base;
        else
            it.next();
    }

    return NULL;
}

uint8_t *BlockBuffer::createBlock(unsigned int id)
{
    uint8_t *block = this->getBlock(id);

    if(block == NULL)
    {
        block = (uint8_t*) malloc(this->block_size);
        this->blocks->pushBack({id, block});
    }

    return block;
}

void BlockBuffer::removeBlock(unsigned int id)
{
    ListIterator<struct buffer_block> it = ListIterator<struct buffer_block>(this->blocks);

    while(! it.isLast())
    {
        if(it.getCurrent().id == id)
        {
            it.remove();
            return;
        }
        else
            it.next();
    }
}

size_t BlockBuffer::read(uintptr_t offset, uint8_t *data, size_t length)
{
    // calculate block indices
    int block_id  = offset / this->block_size;
    int block_off = offset % this->block_size;

    // search first block
    uint8_t *block = this->getBlock(block_id);

    // go through all bytes...
    int i;
    for(i = 0; i < length; i++)
    {
        // if the block ends, go to the next
        if(block_off >= this->block_size)
        {
            block = this->getBlock(++block_id);
            block_off = 0;
        }

        if(block == NULL)
            break;

        // copy data
        data[i] = block[block_off++];
    }

    return i;
}

size_t BlockBuffer::write(uintptr_t offset, const uint8_t *data, size_t length)
{
    // calculate block indices
    int block_id  = offset / this->block_size;
    int block_off = offset % this->block_size;

    // search first block
    uint8_t *block = this->createBlock(block_id);

    // go through all bytes...
    int i;
    for(i = 0; i < length; i++)
    {
        // if the block ends, go to the next
        if(block_off >= this->block_size)
        {
            block = this->createBlock(++block_id);
            block_off = 0;
        }

        // copy data
        block[block_off++] = data[i];
    }

    return i;
}


