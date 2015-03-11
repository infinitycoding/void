#ifndef _void_h_
#define _void_h_

#include <sys/types.h>

void sig_register(pid_t pid);
void sig_command(pid_t pid);


int init_linux(void);

#endif

