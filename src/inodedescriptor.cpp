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

