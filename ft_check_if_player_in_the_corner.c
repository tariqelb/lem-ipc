#include "./lemipc.h"

int	ft_check_if_player_in_the_corner(t_player *player)
{
	printf("ft_check_if_player_in_the_corner\n");
	int	team_array_index;

	if (player->pos_x == 0 && player->pos_y == 0)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			player->game->teams[team_array_index].corner--;	
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == BOARD_X_LEN - 1 && player->pos_y == 0)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			player->game->teams[team_array_index].corner--;	
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == 0 && player->pos_y == BOARD_Y_LEN - 1)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			player->game->teams[team_array_index].corner--;
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	else if (player->pos_x == BOARD_X_LEN - 1 && player->pos_y == BOARD_Y_LEN - 1)
	{
		team_array_index = ft_get_team_array_index(player);
		if (team_array_index != -1)
		{
			player->game->teams[team_array_index].corner--;
		}
		if (player->game->teams[team_array_index].corner <= 0)
			return (-1);
	}
	return (0);
}
