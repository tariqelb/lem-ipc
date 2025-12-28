#include "./lemipc.h"

int	ft_check_if_team_exist(t_player *player)
{
	int i;

	i = 0;
	while (i < MAX_TEAMS)
	{
		if (player->game->teams[i].team_id == player->team_id)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_get_free_place_in_team_array(t_player *player)
{
	int	i;

	i = 0;
	while (i < MAX_TEAMS)
	{
		if (player->game->teams[i].nbr_of_players <= 0)
			return (i);
		i++;
	}
	return (-1);
}

t_player	*ft_initialize_player(t_player *player)
{
	int	team_exist;
	int	x;
	int	y;

	team_exist = ft_check_if_team_exist(player);
	if (team_exist == -1)
	{
		//case when the player is first player in new team
		team_exist = ft_get_free_place_in_team_array(player);
		semop(player->semid, &player->lock_op, 1);
		player->game->teams[team_exist].team_id = player->team_id;
		player->game->teams[team_exist].nbr_of_players = 1;
		player->game->teams[team_exist].corner = 1;
		player->game->total_players++;		
		player->game->total_teams++;		
		player->player_id = 1;
		player->first_move = 1;
		player->died = 0;
	}
	else
	{
		semop(player->semid, &player->lock_op, 1);
		player->game->teams[team_exist].nbr_of_players++;	
		player->game->teams[team_exist].corner++;		
		player->game->total_players++;		
		player->died = 0;
		player->first_move = 1;
		player->player_id = player->game->teams[team_exist].nbr_of_players;
	}
	if (player->team_id % 4 == 0)
	{
		x = player->team_id % BOARD_X_LEN;
		y = 0;
	}
	if (player->team_id % 4 == 1)
	{
		x = BOARD_X_LEN - 1;
		y = player->team_id % BOARD_Y_LEN;
	}
	if (player->team_id % 4 == 2)
	{
		x = player->team_id % BOARD_X_LEN;
		y = BOARD_Y_LEN - 1;
	}
	if (player->team_id % 4 == 3)
	{
		x = 0;
		y = player->team_id % BOARD_Y_LEN;
	}
	player->game->teams[team_exist].init_x = x;
	player->game->teams[team_exist].init_y = y;
	semop(player->semid, &player->unlock_op, 1);
	player->pos_x = -1;
	player->pos_y = -1;
	player->target_team_id = -1;
	return (player);
}
