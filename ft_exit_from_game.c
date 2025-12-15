#include "./lemipc.h"

int	ft_exit_from_game(t_player *player, int flag)
{
	int	player_team_array_index;

	team_array_index = ft_get_team_array_index(player);
	//check if last player before destroy resources
	//team ajustement needed here
	if (player->died == 0)
	{
		semop(player->semid, &player->lock_op, 1);
		if (team_array_index > 0)
		{
			player->game->teams[team_array_index].nbr_of_players--;
			if (player->game->teams[team_array_index].nbr_of_players <= 0)
				player->game->total_teams--;
		}	
		player->game->total_players--;
		semop(player->semid, &player->unlock_op, 1);
	}

	if (player->game->total_players == 0)
	{
		//check for last player before destroy
		if (flag >= 3)
			ft_destroy_message_queue(player);
		//Destroy semaphore
		if (flag >= 2)
			ft_destroy_semaphore(player);
		//Destroy shared memory
		if (flag >= 1)
			ft_remove_shared_memory(player);
	}
	write(1, "Lemipc: Player exit from the game\n", 34);
	return (0);
}

int	ft_player_died(t_player *player)
{
	int	player_team_array_index;

	team_array_index = ft_get_team_array_index(player);
	//check if last player before destroy resources
	//team ajustement needed here
	if (player->died == 0)
	{
		semop(player->semid, &player->lock_op, 1);
		if (team_array_index > 0)
		{
			player->game->teams[team_array_index].nbr_of_players--;
			if (player->game->teams[team_array_index].nbr_of_players <= 0)
				player->game->total_teams--;
		}	
		player->game->total_players--;
		semop(player->semid, &player->unlock_op, 1);
	}

	//check for last player before destroy
	if (player->game->total_players == 0)
	{
		//Destroy message queue
		ft_destroy_message_queue(player);
		//Destroy semaphore
		ft_destroy_semaphore(player);
		//Destroy shared memory
		ft_remove_shared_memory(player);
	}
	write(1, "Lemipc: Player died\n", 20);
	exit(0);
	return (0);
}
