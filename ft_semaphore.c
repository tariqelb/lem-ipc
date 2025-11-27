#include "./lemipc.h"


int	ft_create_semaphore(t_player *player)
{
	// Try to create new semaphore
	player->semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (player->semid != -1)
	{
		// First player - initialize semaphore to 1 (unlocked)
		semctl(player->semid, 0, SETVAL, 1);
		write(1, "Lemipc: Semaphore created and initialized\n", 42);
		return (0);
	}

	// Semaphore exists - attach to existing
	if (errno == EEXIST)
	{
		player->semid = semget(SEM_KEY, 1, 0666);
		if (player->semid == -1)
		{
			write(2, "Lemipc: Fail attaching to existing semaphore\n", 45);
			return (1);
	    	}
		else
		{
			write(1, "Lemipc: Player get semaphore id\n", 32);
			return (0);
		}
	}

	// Error case
	write(2, "Lemipc: Error creating/accessing semaphore\n", 43);
	return (1);
}

int	ft_destroy_semaphore(t_player *player)
{
	int status;

	status = semctl(player->semid, 0, IPC_RMID);
	if (status == 0)
	{
		write(1, "Lemipc: Semaphore destroyed\n", 28);
		return (0);
	}
	else
	{
		write(2, "Lemipc: Error destroying semaphore\n", 36);
		return (1);
	}
}
