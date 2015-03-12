#include "void.h"
#include "client.h"

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
#ifdef __linux__
    init_linux();
#endif

    return 0;
}

