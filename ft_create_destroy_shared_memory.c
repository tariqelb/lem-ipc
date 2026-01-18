#include "./lemipc.h"

int	ft_check_if_max_teams_or_players_reached(t_player *player)
{
	ft_putstr("ft_check_if_max_teams_or_players_reached\n");
	int	nbr_of_team;
	int	i;

	nbr_of_team = 0;
	i = 0;
	while (i < MAX_TEAMS)
	{
		if (player->game->teams[i].nbr_of_players > 0)
			nbr_of_team++;
		if (player->team_id == player->game->teams[i].team_id)
		{
			if (player->game->teams[i].nbr_of_players >= MAX_PLAYER_IN_TEAM)
			{
				write(1, "Lemipc: Max player in team reached\n", 36);
				write(1, "Lemipc: Player exit from the game\n", 35);
				return (1);
			}
		}
		i++;
	}
	if (nbr_of_team >= MAX_TEAMS)
	{
		write(1, "Lemipc: Max teams allowed reached\n", 35);
		write(1, "Lemipc: Player exit from the game\n", 35);
		return (1);
	}
	return (0);
}

int ft_create_shared_memory(t_player *player)
{
	ft_putstr("ft_create_shared_memory\n");
	size_t size;

	size = SHM_SIZE;
	semop(player->semid, &player->lock_op, 1);
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
			semop(player->semid, &player->unlock_op, 1);
			return (1);
		}
		
		// INITIALIZE the game board (first player responsibility)
		player = ft_initialize_game_board(player);
		semop(player->semid, &player->unlock_op, 1);
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
			semop(player->semid, &player->unlock_op, 1);
			return (1);
		}
		else
		{
			// ATTACH to existing shared memory
			player->game = (t_game *)shmat(player->shmid, NULL, 0);
			if (player->game == (void *)-1)
			{
				semop(player->semid, &player->unlock_op, 1);
				write(2, "Lemipc: Failed to attach to existing shared memory\n", 49);
				return (1);
			}
			write(1, "Lemipc: Attached to existing shared memory\n", 43);
			//after attach player to shared memory 
			//we check for if we reach max teams allowed
			//if the player is from an exist team and max teams reached
			//then the player exit from the game
			//ft_check_team_max();
			if (ft_check_if_max_teams_or_players_reached(player))
			{
				semop(player->semid, &player->unlock_op, 1);
				return (1);
			}



			//this need modification , new player need semaphore to make 
			//changes on shared memory
			semop(player->semid, &player->unlock_op, 1);
			player = ft_initialize_player(player);	
			return (0);
		}
	}
	//CRITICAL ERROR: Cannot create or access shared memory
	write(2, "Lemipc: Critical error - cannot access shared memory\n", 52);
	semop(player->semid, &player->unlock_op, 1);
	return (1);
}

int     ft_remove_shared_memory(t_player *player)
{
	ft_putstr("ft_remove_shared_memory\n");
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
