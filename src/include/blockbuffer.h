#ifndef _blockbuffer_h_
#define _blockbuffer_h_
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
#include <stdint.h>
#include "list.h"

struct buffer_block
{
    unsigned int id;
    size_t length;
    void *base;
};

class BlockBuffer : public List<struct buffer_block*>
    {
public:
        BlockBuffer(size_t block_size_);
        ~BlockBuffer();

        struct buffer_block* getBlock(unsigned int id);
        unsigned int getID(void);

        struct buffer_block* createBlock(unsigned int id);
        struct buffer_block* createBlock(unsigned int id, void *base);
        struct buffer_block* removeBlock(unsigned int id);
        struct buffer_block* removeBlock(void *base);

        size_t read(uintptr_t offset, uint8_t *data, size_t length);
        size_t write(uintptr_t offset, const uint8_t *data, size_t length);

private:
        size_t block_size;
    };

#endif

