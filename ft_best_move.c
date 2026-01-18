#include "./lemipc.h"

int	ft_best_move(t_player *player, int *x, int *y)
{
	//ft_putstr("ft_best_move\n");
	int	top;
	int	right;
	int	bottom;
	int	left;
	int	top_top;
	int	right_right;
	int	bottom_bottom;
	int	left_left;

	//best move is a move where you can suround an enemy by just move one step

	*x = 0;
	*y = 0;
	top = -1;
	right = -1;
	bottom = -1;
	left = -1;
	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];

	top_top = -1;
	right_right = -1;
	bottom_bottom = -1;
	left_left = -1;
	

	if (player->pos_x > 1)
		left_left = player->game->board[player->pos_y][player->pos_x - 2];
	if (player->pos_x < BOARD_X_LEN - 2)
		right_right = player->game->board[player->pos_y][player->pos_x + 2];
	if (player->pos_y > 1)
		top_top = player->game->board[player->pos_y - 2][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 2)
		bottom_bottom = player->game->board[player->pos_y + 2][player->pos_x];


	if (top == 0 && top_top > 0 && top_top != player->team_id + 1 && player->pos_y > 2)
	{
		int	top_3;

		top_3 = player->game->board[player->pos_y - 3][player->pos_x];
		if (top_3 > 0 && top_top != top_3)
		{
			*y = -1;
			return (0);
		}
	}
	if (right == 0 && right_right > 0 && right_right != player->team_id + 1 && player->pos_x < BOARD_X_LEN - 3)
	{
		int	right_3;

		right_3 = player->game->board[player->pos_y][player->pos_x + 3];
		if (right_3 > 0 && right_right != right_3)
		{
			*x = 1;
			return (1);
		}
	}
	if (bottom == 0 && bottom_bottom > 0 && bottom_bottom != player->team_id + 1 && player->pos_y < BOARD_Y_LEN - 3)
	{
		int	bottom_3;

		bottom_3 = player->game->board[player->pos_y + 3][player->pos_x];
		if (bottom_3 > 0 && bottom_bottom != bottom_3)
		{
			*y = 1;
			return (2);
		}
	}
	if (left == 0 && left_left > 0 && left_left != player->team_id + 1 && player->pos_x > 2)
	{
		int	left_3;

		left_3 = player->game->board[player->pos_y][player->pos_x - 3];
		if (left_3 > 0 && left_left != left_3)
		{
			*x = -1;
			return (3);
		}
	}
	return  (-1);
}



int	ft_second_best_move(t_player *player, int *x, int *y)
{
	ft_putstr("ft_second_best_move\n");
	int	top_left;
	int	top_right;
	int	btm_right;
	int	btm_left;

	top_left  = -1;
	top_right = -1;
	btm_right = -1;
	btm_left  = -1;

	if (player->pos_x > 0 && player->pos_y > 0)
		top_left = player->game->board[player->pos_y - 1][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y > 0)
		top_right = player->game->board[player->pos_y - 1][player->pos_x + 1];
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y < BOARD_Y_LEN - 1)
		btm_right = player->game->board[player->pos_y + 1][player->pos_x  + 1];
	if (player->pos_x > 0 && player->pos_y < BOARD_Y_LEN - 1)
		btm_left = player->game->board[player->pos_y + 1][player->pos_x - 1];

	if (top_left > 0 && top_left != player->team_id + 1)
	{
		int e_top;
		int e_right;
		int e_bottom;
		int e_left;

		ft_get_position_sides(player, player->pos_x - 1, player->pos_y - 1, &e_top, &e_right, &e_bottom, &e_left);
		if (e_top > 0 && e_top != top_left && e_bottom == 0)
		{
			*x = -1;
			*y = 0;
			return (1);
		}
		if (e_left > 0 && e_left != top_left && e_right == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}
	}
	if (top_right > 0 && top_right != player->team_id + 1)
	{
		int e_top;
		int e_right;
		int e_bottom;
		int e_left;

		ft_get_position_sides(player, player->pos_x + 1, player->pos_y - 1, &e_top, &e_right, &e_bottom, &e_left);
		if (e_top > 0 && e_top != top_right && e_bottom == 0)
		{
			*x = 1;
			*y = 0;
			return (1);
		}
		if (e_right > 0 && e_right != top_right && e_left == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}
	}
	if (btm_right > 0 && btm_right != player->team_id + 1)
	{
		int e_top;
		int e_right;
		int e_bottom;
		int e_left;

		ft_get_position_sides(player, player->pos_x + 1, player->pos_y + 1, &e_top, &e_right, &e_bottom, &e_left);
		if (e_bottom > 0 && e_bottom != btm_right && e_top == 0)
		{
			*x = 1;
			*y = 0;
		}
		if (e_right > 0 && e_right != btm_right && e_left == 0)
		{
			*x = 0;
			*y = 1;
		}

	}
	if (btm_left > 0 && btm_left != player->team_id + 1)
	{
		int e_top;
		int e_right;
		int e_bottom;
		int e_left;

		ft_get_position_sides(player, player->pos_x - 1, player->pos_y + 1, &e_top, &e_right, &e_bottom, &e_left);
		if (e_bottom > 0 && e_bottom != btm_left && e_top == 0)
		{
			*x = -1;
			*y = 0;
			return (1);
		}
		if (e_left > 0 && e_left != btm_left && e_right == 0)
		{
			*x = 0;
			*y = 1;
			return (1);
		}
	}
	
	return (-1);
}
