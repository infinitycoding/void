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
#include "void.h"

#include <stdio.h>

FileDescriptor::FileDescriptor(InodeDescriptor *read_, InodeDescriptor *write_)
    : read_descriptor(read_), write_descriptor(write_)
{
}

FileDescriptor::~FileDescriptor()
{
}

size_t FileDescriptor::read(void *data, size_t length)
{
    if(this->read_descriptor != NULL)
    {
        return this->read_descriptor->read(data, length);
    }
    return 0;
}

size_t FileDescriptor::write(const void *data, size_t length)
{
    if(this->write_descriptor != NULL)
    {
        return this->write_descriptor->write(data, length);
    }
    return 0;
}

