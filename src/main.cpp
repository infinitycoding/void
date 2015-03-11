#include <void.h>

#include <stdio.h>
#include <stdlib.h>

void sig_register(pid_t pid)
{
	printf("[VOID] got request from pid %d\n", pid);

	printf("[VOID] terminating..\n");
	exit(0);
}

void sig_command(pid_t pid)
{
	
}

int main(int argc, char **argv)
{
	init_linux();

	return 0;
}

