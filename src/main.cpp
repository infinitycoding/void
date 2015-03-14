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
#include "void.h"
#include "client.h"
#include "inode.h"

#include <stdio.h>
#include <stdlib.h>

Client *client;

void sig_register(int id)
{
    printf("[VOID] register client with id %d\n", id);
    client = new Client(id);
}

void sig_command(int id)
{
    client->command();
}

int main(int argc, char **argv)
{
    printf("[VOID] create Inode..\n");
    Inode *inode = new Inode();
    InodeDescriptor *desc0 = new InodeDescriptor(inode);
    InodeDescriptor *desc1 = new InodeDescriptor(inode);
    FileDescriptor *desc = new FileDescriptor(desc0, desc1);

    desc->write("Hallo", 6);

    char buf[16];
    desc->read(&buf, 6);

    printf("%s\n", buf);


#ifdef __linux__
    init_linux();
#endif

    return 0;
}

