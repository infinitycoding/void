#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
	printf("Hello Universe!\n");

	int shm_id = shmget(IPC_PRIVATE, 0x1000, IPC_CREAT | SHM_R | SHM_W);

	if(shm_id == -1)
	{
		printf("error creating shm segment\n");
	}
	else
	{
		void *base = shmat(shm_id, 0, 0);
		printf("shm at adress 0x%x\n", base);
	}

	return 0;
}

