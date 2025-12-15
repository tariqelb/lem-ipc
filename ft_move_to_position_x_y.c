#include "./lemipc.h"

int	ft_move_to_position_x_y(t_player *player, int x, int y)
{
	if (x == -1 || y == -1)
		return (1);
	if (player->game->board[x][y] != 0)
		return (1);
	semop(player->semid, &player->lock_op, 1);
	player->game->board[x][y] = player->team_id + 1;
	semop(player->semid, &player->unlock_op, 1);
	return (0);
}
