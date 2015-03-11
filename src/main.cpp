#include "void.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>

void sig_register(int id)
{
	printf("[VOID] register client with id %d\n", id);
	Client *client = new Client(id);
}

void sig_command(int id)
{
	printf("[VOID] have to execute command for %d\n", id);
}

int main(int argc, char **argv)
{
	#ifdef __linux__
	init_linux();
	#endif

	return 0;
}

