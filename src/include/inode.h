#ifndef _inode_h_
#define _inode_h_
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

class DirectoryInode;
class Inode
{
    public:
        Inode();
        Inode(const char *name_);
        Inode(const char *name_, DirectoryInode *parent_);
        ~Inode();

        const char *name;

        size_t read(unsigned int buffer, uintptr_t offset, void *data, size_t length);
        size_t write(unsigned int buffer, uintptr_t offset, const void *data, size_t length);

        void setParent(DirectoryInode *parent_);

        char *generatePath(void);
        char *generatePath(char *buffer);

        unsigned int getID(void);

    protected:
        DirectoryInode *parent;

        size_t num_buffers;
        BlockBuffer **buffers;

        void init_buffers(size_t num, size_t size);

    private:
        unsigned int id;
};

Inode *lookup_path(const char *path);

#endif

