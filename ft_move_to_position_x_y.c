#include "./lemipc.h"

int	ft_move_to_position_x_y(t_player *player, int x, int y)
{
	ft_putstr("ft_move_to_position_x_y\n");
	if (x < 0 || y < 0 || x >= BOARD_X_LEN || y >= BOARD_Y_LEN)
		return (1);
	if (player->game->board[y][x] != 0)
		return (1);
	//check if player return to last position , if yes , check if this position surround enemy, if no, just skip this move
	if (ft_check_if_last_position_surround_enemy(player, x, y) == 0)
		return (1);
	if (player->game->board[y][x] == 0)
	{
		player->game->board[player->pos_y][player->pos_x] = 0;
		player->game->board[y][x] = player->team_id + 1;
		player->last_x_pos = player->pos_x;
		player->last_y_pos = player->pos_y;
		player->pos_x = x;
		player->pos_y = y;
		player->find_path_active = 0;
	}
	return (0);
}
