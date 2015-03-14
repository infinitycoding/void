#ifndef _process_h_
#define _process_h_
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
#include "list.h"
#include "descriptor.h"

class Client
{
    public:
        Client(int id);
        ~Client();

        int id;

        void command(void);

        FileDescriptor *getDesc(int fd);

        int open(const char *path);
        int close(int fd);
        int read(int fd, void *buffer, size_t length);
        int write(int fd, const void *buffer, size_t length);

    private:
        int shm_id;
        struct command_data *data;

        List<FileDescriptor*> *files;
};

#endif

