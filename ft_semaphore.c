#include "./lemipc.h"


// System V semaphore operations
//struct sembuf lock = {0, -1, SEM_UNDO};    // Wait/Lock
//struct sembuf unlock = {0, 1, SEM_UNDO};   // Post/Unlock

// Lock the shared resource
//semop(player->semid, &lock, 1);

// Critical section - access shared memory
//player->game->board[5][10] = player->team_id;

// Unlock  
//semop(player->semid, &unlock, 1);


void	ft_initialize_semaphore_struct(t_player *player)
{
	player->lock_op.sem_num = 0;
	player->lock_op.sem_op = -1;
	player->lock_op.sem_flg = SEM_UNDO;

	player->unlock_op.sem_num = 0;
	player->unlock_op.sem_op = 1;
	player->unlock_op.sem_flg = SEM_UNDO;
}

int	ft_create_semaphore(t_player *player)
{
	//ft_putstr("ft_create_semaphore\n");
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
	//ft_putstr("ft_destroy_semaphore\n");
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
