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
#include <string.h>
#include <stdlib.h>

DirectoryInode::DirectoryInode()
{
    this->name = NULL;
    this->parent = NULL;
    this->init_buffers(1, sizeof(Inode*));
}

DirectoryInode::DirectoryInode(const char *name_)
{
    this->name = NULL;
    this->setName(name_);
    this->parent = NULL;
    this->init_buffers(1, sizeof(Inode*));
}

DirectoryInode::DirectoryInode(const char *name_, DirectoryInode *parent_)
{
    this->name = NULL;
    this->setName(name_);
    this->parent = NULL;
    this->setParent(parent_);
    this->init_buffers(1, sizeof(Inode*));
}

DirectoryInode::~DirectoryInode()
{
}

void DirectoryInode::addEntry(Inode *inode)
{
    this->buffers[0]->createBlock(this->buffers[0]->getID(), inode);
}

void DirectoryInode::removeEntry(Inode *inode)
{
    free(this->buffers[0]->removeBlock(inode));
}

Inode *DirectoryInode::getEntry(const char *path)
{
    static char delimiter[] = "/";
    size_t n = 0;
    while(path[n] != '/' && path[n] != '\0') n++;

    Inode *inode = NULL;
    if(n > 0)
    {
        ListIterator<struct buffer_block*> it = ListIterator<struct buffer_block*>(this->buffers[0]);

        while(! it.isLast())
        {
            Inode *in = (Inode*) it.getCurrent()->base;
            if(in != NULL && in->name != NULL && strncmp(in->name, path, n) == 0)
            {
                inode = in;
                break;
            }
            else
            {
                it.next();
            }
        }
    }
    else
        inode = (Inode*) this;

    if(inode != NULL)
    {
        if(path[n] != '\0')
        {
            DirectoryInode *parent = dynamic_cast<DirectoryInode*>(inode);
            if(parent != NULL)
                return parent->getEntry(path + n + 1);
            else
                return NULL;
        }
        else
            return inode;
    }

    return NULL;
}

