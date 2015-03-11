#ifndef _void_h_
#define _void_h_

#include <sys/types.h>

enum command
{
	OPEN,
	CLOSE,
	READ,
	WRITE
};

void sig_register(int id);
void sig_command(int id);

#ifdef __linux__
int init_linux(void);
#endif

#ifdef __universe__ // ??
int init_universe(void);
#endif

#endif

