#ifndef _blockbuffer_h_
#define _blockbuffer_h_

#include <stdint.h>
#include "list.h"

struct buffer_block
{
    unsigned int id;
    uint8_t *base;
};

class BlockBuffer
{
    public:
        BlockBuffer(size_t block_size_);
        ~BlockBuffer();

        uint8_t *getBlock(unsigned int id);
        uint8_t *createBlock(unsigned int id);
        void removeBlock(unsigned int id);

        int read(uintptr_t offset, uint8_t *data, size_t length);
        int write(uintptr_t offset, const uint8_t *data, size_t length);

    private:
        List<struct buffer_block> *blocks;
        size_t block_size;
};

#endif

