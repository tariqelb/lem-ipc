#include "./lemipc.h"

int	ft_leave_the_board(t_player *player)
{
	int	team_array_index;

	team_array_index = ft_get_team_array_index(player);
	player->died = 1;
	semop(player->semid, &player->lock_op, 1);
	player->game->board[player->pos_x][player->pos_y] = 0;
	if (team_array_index > 0)
	{
		player->game->teams[team_array_index].nbr_of_players--;
		if (player->game->teams[team_array_index].nbr_of_players == 0)
			player->game->total_teams--;
	}
	player->game->total_players--;
	semop(player->semid, &player->unlock_op, 1);
	return (0);
}
