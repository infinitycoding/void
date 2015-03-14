#ifndef _void_h_
#define _void_h_
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
#include <sys/types.h>

enum command
{
    OPEN,
    CLOSE,
    READ,
    WRITE
};

struct arg_open
{
    int modus;
};

struct arg_close
{
    int fd;
};

struct arg_read
{
    int fd;
    size_t length;
};

struct arg_write
{
    int fd;
    size_t length;
};

struct command_data
{
    enum command cmd;
    int ret;
    union
    {
        struct arg_open arg_open;
        struct arg_close arg_close;
        struct arg_read arg_read;
        struct arg_write arg_write;
    };
};

void sig_register(int id);
void sig_command(int id);

#ifdef __linux__
int init_linux(void);
#endif

#ifdef __universe__ // ??
int init_universe(void);
#endif


void *create_shm(int *shm_id);

#endif

