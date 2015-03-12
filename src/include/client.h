#ifndef _process_h_
#define _process_h_

#include <void.h>


class Client
{
	public:
		Client(int id);
		~Client();

		int id;

		void command(void);

		void open(void *ret, const char *path);
		void close(void *ret, int fd);
		void read(void);
		void write(void);

	private:
		int shm_id;
		struct command_data *data;
};

#endif

