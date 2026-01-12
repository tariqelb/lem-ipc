#include "lemipc.h"

int	ft_check_if_last_position_surround_enemy(t_player *player, int new_x, int new_y)
{
	//some times player block in position and find path get him out , but may next move bring him back to the same position
	//here we will check if its goes to last position , if yes , we will let player go back only if this position will surround an enemy
	printf("ft_check_if_last_position_surround_enemy\n");
	if (player->last_x_pos == new_x && player->last_y_pos == new_y)
	{
		int	player_id;

		player_id = player->team_id + 1;
		if (new_y > 1)
		{
			int	new_pos_top_top;
			int	new_pos_top;

			new_pos_top = -1;
			new_pos_top_top = -1;

			new_pos_top = player->game->board[new_y - 1][new_x];
			new_pos_top_top = player->game->board[new_y - 2][new_x];
			if (new_pos_top > 0 && new_pos_top_top > 0 && new_pos_top != player_id && new_pos_top != new_pos_top_top)
			{
				return (1);
			}
		}
		if (new_x < BOARD_X_LEN - 2)
		{
			int	new_pos_right_right;
			int	new_pos_right;

			new_pos_right = -1;
			new_pos_right_right = -1;

			new_pos_right = player->game->board[new_y][new_x + 1];
			new_pos_right_right = player->game->board[new_y][new_x + 2];
			if (new_pos_right > 0 && new_pos_right_right > 0 && new_pos_right != player_id && new_pos_right != new_pos_right_right)
			{
				return (1);
			}
		}
		if (new_y < BOARD_Y_LEN - 2)
		{
			int	new_pos_bottom_btm;
			int	new_pos_bottom;

			new_pos_bottom = -1;
			new_pos_bottom_btm = -1;

			new_pos_bottom = player->game->board[new_y + 1][new_x];
			new_pos_bottom_btm = player->game->board[new_y + 2][new_x];
			if (new_pos_bottom > 0 && new_pos_bottom_btm > 0 && new_pos_bottom != player_id && new_pos_bottom != new_pos_bottom_btm)
			{
				return (1);
			}
		}
		if (new_x > 1)
		{
			int	new_pos_left_left;
			int	new_pos_left;

			new_pos_left = -1;
			new_pos_left_left = -1;

			new_pos_left = player->game->board[new_y][new_x - 1];
			new_pos_left_left = player->game->board[new_y][new_x - 2];
			if (new_pos_left > 0 && new_pos_left_left > 0 && new_pos_left != player_id && new_pos_left != new_pos_left_left)
			{
				return (1);
			}
		}
		return (0);

	}
	return (1);
}
