#include "./lemipc.h"


int	ft_move_to_best_position(t_player *player, int *x, int *y)
{
	printf("ft_move_to_best_position\n");
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

	printf("Data : t[%d]r[%d]b[%d]l[%d] tl[%d]tr[%d]br[%d]bl[%d]\n", top, right, bottom, left, top_left, top_right, bottom_right, bottom_left);
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
		if (bottom_left > 0 && bottom_left != left && top_left == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}

	}

	return (0);
}


int	ft_move_to_second_best_position(t_player *player, int *x, int *y)
{
	printf("ft_move_to_second_best_position\n");
	//ex of case work on
	//[0][0][0][0][0] 
	//[x][E][P][0][0] 
	//[0][0][p][0][0] 
	//[0][0][0][0][0] 
	//[0][0][0][0][0] 
	//check and move to left to fill x position 

	int	top;
	int	right;
	int	bottom;
	int	left;

	int	player_id;

	int	top_left;
	int	top_right;
	int	btm_left;
	int	btm_right;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;

	top_left = -1;
	top_right = -1;
	btm_left = -1;
	btm_right = -1;

	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];

	player_id = player->team_id + 1;

	if (player->pos_x > 0 && player->pos_y > 0)
		top_left = player->game->board[player->pos_y - 1][player->pos_x - 1];	
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y > 0)
		top_right = player->game->board[player->pos_y - 1][player->pos_x + 1];
	if (player->pos_x > 0 && player->pos_y < BOARD_Y_LEN - 1)
		btm_left = player->game->board[player->pos_y + 1][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1 && player->pos_y < BOARD_Y_LEN - 1)
		btm_right = player->game->board[player->pos_y + 1][player->pos_x + 1];

	//top and top-left (x is left-top_left)
	if (top > 0 && top_left > 0 && top_left != top && top_left != player_id)
	{
		int	left_top_left = -1;

		if (player->pos_x > 1)
			left_top_left = player->game->board[player->pos_y - 1][player->pos_x - 2];
		if (left_top_left == 0 && left == 0)
		{
			*x = -1;
			*y = 0;
			return (1);
		}
	}
	//top and top-right (x right-top_right) 
	if (top > 0 && top_right > 0 && top_right != top && top_right != player_id)
	{
		int	right_top_right = -1;

		if (player->pos_x < BOARD_X_LEN - 2)
			right_top_right = player->game->board[player->pos_y - 1][player->pos_x + 2];
		if (right_top_right == 0 && right == 0)
		{
			*x = 1;
			*y = 0;
			return (1);
		}
	}
	//bottom and btm-left (x is left-btm_left)
	if (bottom > 0 && btm_left > 0 && btm_left != bottom && btm_left != player_id)
	{
		int	left_btm_left = -1;

		if (player->pos_x > 1)
			left_btm_left = player->game->board[player->pos_y + 1][player->pos_x - 2];
		if (left_btm_left == 0 && left == 0)
		{
			*x = -1;
			*y = 0;
			return (1);
		}
	}
	//bottom && btm_right (x is right-btm_right)
	if (bottom > 0 && btm_right > 0 && btm_right != bottom && btm_right != player_id)
	{
		int	right_btm_right = -1;

		if (player->pos_x < BOARD_X_LEN - 2)
			right_btm_right = player->game->board[player->pos_y + 1][player->pos_x + 2];
		if (right_btm_right == 0 && right == 0)
		{
			*x = 1;
			*y = 0;
			return (1);
		}
	}

	//[0][0][0][0][0]
	//[0][x][0][0][0]
	//[0][E][0][0][0]
	//[0][P][p][0][0]
	//[0][0][0][0][0]
	//
	//(x is top-top_left)
	if (left > 0 && top_left > 0 && left != top_left && top_left != player_id)
	{
		int	top_top_left = -1;
		
		if (player->pos_y > 1)
			top_top_left = player->game->board[player->pos_y - 2][player->pos_x - 1];
		if (top_top_left == 0 && top == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}
	}
	//(x is top-top_right)
	if (right > 0 && top_right > 0 && right != top_right && top_right != player_id)
	{
		int	top_top_right = -1;

		if (player->pos_y > 1)
			top_top_right = player->game->board[player->pos_y - 2][player->pos_x - 1];
		if (top_top_right == 0 && top == 0)
		{
			*x = 0;
			*y = -1;
			return (1);
		}
	}
	//(x is bottom-btm_left)
	if (left > 0 && btm_left > 0 && left != btm_left && btm_left != player_id)
	{
		int	bottom_btm_left;

		if (player->pos_y < BOARD_Y_LEN - 2)
			bottom_btm_left = player->game->board[player->pos_y + 2][player->pos_x - 1];
		if (bottom_btm_left == 0 && bottom == 0)
		{
			*x = 0;
			*y = 1;
			return (0);
		}
	}
	if (right > 0 && btm_right > 0 && right != btm_right && btm_right != player_id)
	{
		int	bottom_btm_right = -1;

		if (player->pos_y < BOARD_Y_LEN - 2)
			bottom_btm_right = player->game->board[player->pos_y + 2][player->pos_x + 1];
		if (bottom_btm_right == 0 && bottom == 0)
		{
			*x = 0;
			*y = 1;
			return (1);
		}
	}
	return (0);
}
