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

    inode->write(0, 0, "Hallo", 6);

    char buf[16];
    inode->read(0, 0, &buf, 6);

    printf("%s\n", buf);


#ifdef __linux__
    init_linux();
#endif

    return 0;
}

