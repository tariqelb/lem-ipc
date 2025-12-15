#include "./lemipc.h"

int	ft_check_if_player_in_the_corner(t_player *player)
{
	int	team_array_index;

	if (player->pos_x == 0 && player->pos_y == 0)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			semop(player->semid, &player->lock_op, 1);
			player->game->teams[team_array_index].corner--;	
			semop(player->semid, &player->unlock_op, 1);
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == 31 && player->pos_y == 0)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			semop(player->semid, &player->lock_op, 1);
			player->game->teams[team_array_index].corner--;	
			semop(player->semid, &player->unlock_op, 1);
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == 0 && player->pos_y == 31)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			semop(player->semid, &player->lock_op, 1);
			player->game->teams[team_array_index].corner--;	
			semop(player->semid, &player->unlock_op, 1);
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == 31 && player->pos_y == 31)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			semop(player->semid, &player->lock_op, 1);
			player->game->teams[team_array_index].corner--;	
			semop(player->semid, &player->unlock_op, 1);
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	return (0);
}
