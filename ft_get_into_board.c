#include "./lemipc.h"

int	ft_get_into_board(t_player *player)
{
	int	team_id;
	int	initial_x;
	int	initial_y;
	int	team_index_in_array;
	int	i;

	i = 0;
	team_index_in_array = -1;
	team_id = player->team_id;
	while (i < MAX_TEAMS)
	{
		if (player->game->teams[i].team_id == team_id)
			team_index_in_array = i;
		i++;
	}
	if (team_index_in_array == -1)
		return (1);
	initial_x = player->game->teams[team_index_in_array].init_x;
	initial_y = player->game->teams[team_index_in_array].init_y;
	if (player->pos_x == -1)
	{
		if (player->game->board[initial_y][initial_x] == 0)
		{
			semop(player->semid, &player->lock_op, 1);
			player->game->board[initial_y][initial_x] = 1 + team_id;
			player->pos_x = initial_x;
			player->pos_y = initial_y;
			semop(player->semid, &player->unlock_op, 1);
			return (0);
		}
	}
	return (1);
}
