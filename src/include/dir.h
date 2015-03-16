#ifndef _dir_h_
#define _dir_h_
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

class DirectoryInode : public Inode
{
    public:
        DirectoryInode();
        DirectoryInode(const char *name_);
        DirectoryInode(const char *name_, DirectoryInode *parent_);
        ~DirectoryInode();

        void addEntry(Inode *inode);
        void removeEntry(Inode *inode);
        Inode *getEntry(const char *name);
};

#endif

