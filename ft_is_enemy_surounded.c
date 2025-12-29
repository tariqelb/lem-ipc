#include "./lemipc.h"

int	ft_is_enemy_surounded(t_player *player)
{
	int	top;
	int	right;
	int	bottom;
	int	left;


	//player check by itself if its surrounded
	//two player can surround a enemy and go , and the surroneded player should exit from board
	//the problem here is the died player check if died after get semaphore
	//which can be happen after the other enemy surrouned him move to other position
	//the player is died , its already surouneded but the non-synchronisation check gives false result
	//for that we will force the player that surounde an enemy stay in here position till died player leave

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;
	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN)
		top = player->game->board[player->pos_y + 1][player->pos_x];
	if (top > 0 && top != player->team_id + 1 && player->pos_y > 1)
	{
		int	top_top;

		top_top = player->game->board[player->pos_y - 2][player->pos_x];
		if (top_top > 0 && top_top != top)
			return (1);
	}
	if (right > 0 && right != player->team_id + 1 && player->pos_x < BOARD_X_LEN - 2)
	{
		int	right_right;

		right_right = player->game->board[player->pos_y][player->pos_x + 2];
		if (right > 0 && right_right != right)
			return (1);
	}
	if (bottom > 0 && bottom != player->team_id + 1 && player->pos_y < BOARD_Y_LEN - 2)
	{
		int	bottom_bottom;

		bottom_bottom = player->game->board[player->pos_y + 2][player->pos_x];
		if (bottom > 0 && bottom_bottom != bottom)
			return (1);
	}
	if (left > 0 && left != player->team_id + 1 && player->pos_x > 1)
	{
		int	left_left;

		left_left = player->game->board[player->pos_y][player->pos_x - 2];
		if (left_left > 0 && left_left != left)
			return (1);
	}
	return (0);
}
