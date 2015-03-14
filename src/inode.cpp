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
#include "blockbuffer.h"

Inode::Inode()
{
    this->buffers[0] = new BlockBuffer(0x1000);
    this->buffers[1] = new BlockBuffer(0x1000);
}

Inode::~Inode()
{
}

size_t Inode::read(unsigned int buffer, uintptr_t offset, void *data, size_t length)
{
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->read(offset, (uint8_t*) data, length);
    }
    return 0;
}

size_t Inode::write(unsigned int buffer, uintptr_t offset, const void *data, size_t length)
{
    BlockBuffer *b = this->buffers[buffer];
    if(b != NULL)
    {
        return b->write(offset, (const uint8_t*) data, length);
    }
    return 0;
}

