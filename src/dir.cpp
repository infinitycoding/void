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
#include "dir.h"
#include "blockbuffer.h"
#include "inode.h"

DirectoryInode::DirectoryInode()
{
    this->init_buffers(1, sizeof(Inode*));
}

DirectoryInode::DirectoryInode(const char *name_)
{
    this->name = name_;
    this->init_buffers(1, sizeof(Inode*));
}

DirectoryInode::DirectoryInode(const char *name_, DirectoryInode *parent_)
{
    this->name = name_;
    this->setParent(parent_);
    this->init_buffers(1, sizeof(Inode*));
}

void DirectoryInode::addEntry(Inode *inode)
{
    Inode **inp = (Inode**) this->buffers[0]->createBlock(inode->getID());
    *inp = inode;
}

void DirectoryInode::removeEntry(Inode *inode)
{
    this->buffers[0]->removeBlock(inode->getID());
}

