#ifndef _descriptor_h_
#define _descriptor_h_
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

class InodeDescriptor
{
    public:
        InodeDescriptor(Inode *inode_);
        ~InodeDescriptor();

        Inode *inode;
        int position;

        unsigned int read_buffer;
        unsigned int write_buffer;

        size_t read(void *data, size_t length);
        size_t write(const void *data, size_t length);
};

class FileDescriptor
{
    public:
        FileDescriptor(InodeDescriptor *read_, InodeDescriptor *write_);
        ~FileDescriptor();

        int id;

        InodeDescriptor *read_descriptor;
        InodeDescriptor *write_descriptor;

        size_t read(void *data, size_t length);
        size_t write(const void *data, size_t length);
};

#endif

