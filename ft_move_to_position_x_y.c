#include "./lemipc.h"

int	ft_move_to_position_x_y(t_player *player, int x, int y)
{
	if (x < 0 || y < 0 || x >= BOARD_X_LEN || y >= BOARD_Y_LEN)
		return (1);
	if (player->game->board[y][x] != 0)
		return (1);
	if (player->game->board[y][x] == 0)
	{
		player->game->board[player->pos_y][player->pos_x] = 0;
		player->game->board[y][x] = player->team_id + 1;
		player->pos_x = x;
		player->pos_y = y;
	}
	return (0);
}
