#include "./lemipc.h"

int ft_create_shared_memory(t_player *player)
{
    	size_t size;

	size = SHM_SIZE;

	// Try to create NEW shared memory (fails if exists)
	player->shmid = shmget(SHM_KEY, size, IPC_CREAT | IPC_EXCL | 0666);
    	if (player->shmid != -1)
	{
		//SUCCESS: We're the FIRST player - created new shared memory
		write(1, "Lemipc: Created new shared memory\n", 34);

		// ATTACH to shared memory
		player->game = (t_game *)shmat(player->shmid, NULL, 0);
		if (player->game == (void *)-1)
		{
		    write(2, "Lemipc: Failed to attach to new shared memory\n", 45);
		    return (1);
		}

		// INITIALIZE the game board (first player responsibility)
		player = ft_initialize_game_board(player);
		return (0);
	}

	//FAILED: Check why it failed
	if (errno == EEXIST)
	{
		//Shared memory EXISTS - attach to existing
		player->shmid = shmget(SHM_KEY, size, 0666);
		if (player->shmid == -1)
		{
			write(2, "Lemipc: Fail attaching to existing shared memory\n", 49);
			return (1);
		}
		else
		{
			// ATTACH to existing shared memory
			player->game = (t_game *)shmat(player->shmid, NULL, 0);
			if (player->game == (void *)-1)
			{
				write(2, "Lemipc: Failed to attach to existing shared memory\n", 49);
				return (1);
			}
			write(1, "Lemipc: Attached to existing shared memory\n", 43);
			//after attach player to shared memory 
			//we check for if we ream max team allowed
			//if the player is from new team and max team reached
			//then the player exit or wait till team is less than 100
			//ft_check_team_max();
			player = ft_initialize_player(player);	
			return (0);
		}
	}
	//CRITICAL ERROR: Cannot create or access shared memory
	write(2, "Lemipc: Critical error - cannot access shared memory\n", 52);
	return (1);
}

int     ft_remove_shared_memory(t_player *player)
{
        int     status;

        status = shmctl(player->shmid, IPC_RMID, NULL);
        if (status == 0)
                write(1, "Lemipc: shared memory destroyed\n", 32);
        else
        {
                write(1, "Lemipc: error destrying shared memory\n", 38);
                return (1);
        }
        return (0);
}
