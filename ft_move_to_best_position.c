#include "./lemipc.h"


int	ft_move_to_best_position(t_player *player, int *x, int *y)
{
	int	top;
	int	right;
	int	bottom;
	int	left;

	int     player_id;
	int     top_left;
	int     top_right;
	int     bottom_right;
	int     bottom_left;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;

	top_left = -1;
	top_right = -1;
	bottom_right = -1;
	bottom_left = -1;

	player_id = player->team_id + 1;

	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];


	if (player->pos_x > 0 && player->pos_y > 0)
		top_left = player->game->board[player->pos_y - 1][player->pos_x - 1];	
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y > 0)
		top_right = player->game->board[player->pos_y - 1][player->pos_x + 1];
	if (player->pos_x > 0 && player->pos_y < BOARD_Y_LEN - 1)
		bottom_left = player->game->board[player->pos_y + 1][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y < BOARD_Y_LEN - 1)
		bottom_right = player->game->board[player->pos_y + 1][player->pos_x + 1];

	if (top > 0 && top != player_id)
	{
		if (top_left > 0 && top_left != top && top_right == 0)
		{
			*x = 1;
			*y = 0;
			return (1);
		}
		if (top_right > 0 && top_right != top && top_left == 0)
		{
			*x = -1;
			*y = 0;
			return (0);
		}
	}
	if (right > 0 && right != player_id)
	{
		if (top_right > 0 && top_right != right && bottom_right == 0)
		{
			*x = 0;
			*y = 1;
			return (1);
		}
		if (bottom_right > 0 && bottom_right != right && top_right == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}

	}
	if (bottom > 0 && bottom != player_id)
	{
		if (bottom_right > 0 && bottom_right != bottom && bottom_left == 0)
		{
			*x = -1;
			*y = 0;
			return (1);
		}
		if (bottom_left > 0 && bottom_left != bottom && bottom_right == 0)
		{
			*x = 1;
			*y = 0;
		}

	}
	if (left > 0 && left != player_id)
	{
		if (top_left > 0 && top_left != left && bottom_left == 0)
		{
			*x = 0;
			*y = 1;
			return (1);
		}
		if (bottom_left > 0 && bottom_left != left && bottom_right == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}

	}

	return (0);
}
