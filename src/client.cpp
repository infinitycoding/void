
#include "client.h"
#include "void.h"

#include <stdio.h>

Client::Client(int id_)
: id(id_)
{
	this->data = (struct command_data*) create_shm(&this->shm_id);
}

Client::~Client()
{
}

void Client::command(void)
{
	void *ret = (void*) this->data;
	void *buffer = (void*) this->data + sizeof(struct command_data);

	switch(this->data->cmd)
	{
		case OPEN:
			open(ret, (const char*) buffer);
			break;

		default:
			printf("[VOID] undefined command.\n");
			break;
	}
}

void Client::open(void *ret, const char *path)
{
	printf("[VOID] open \"%s\" for client %d\n", path, this->id);
}

