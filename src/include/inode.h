
#ifndef _inode_h_
#define _inode_h_

class Inode
{
    public:
        Inode();
        ~Inode();

        char *name;
        size_t length;

        Inode *parent;
};

#endif

