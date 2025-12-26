#include "./lemipc.h"

int	ft_check_if_player_need_to_escape_or_died(t_player *player)
{
	//Diagonal positions (do NOT cause death):
	//[E]   [E]
	//   [P]
	//[E]   [E]
	//positions (cause death):
	//                    [E]
	//[E][P][E]    or     [P]
	//                    [E]

	//the case where player need to escape is where player have one enemy in one
	//of fore sides (top, left, bottom, right) and second enemy from the same team
	//in the diagonal side (top-right ...)
	//(top=0 , right=1, bottom=2, leftt=3)
	//(t-right=0, t_right=1, b_left=2, b_left=3)

	int	top_left;
	int	top_right;
	int	btm_left;
	int	btm_right;
	int	top;
	int	right;
	int	bottom;
	int	left;
	int	p_x;
	int	p_y;
	int	t_id;

	top_left  = 0;
	top_right = 0;
	btm_left  = 0;
	btm_right = 0;
	top       = 0;
	right     = 0;
	bottom    = 0;
	left      = 0;
	p_x       = player->pos_x;
	p_y       = player->pos_y;
	t_id      = player->team_id + 1;
	if (player->pos_y == 0 && player->pos_x == 0)
	{//top left of the board
		top_left  = -1;
		top       = -1;
		top_right = -1;
		left      = -1;
		btm_left  = -1;
	}
	else if (player->pos_y == 0 && player->pos_x == BOARD_X_LEN - 1)
	{//top right of the board
		top_right = -1;
		top       = -1;
		top_left  = -1;
		right     = -1;
		btm_right = -1;
	}
	else if (player->pos_x == 0 && player->pos_y == BOARD_Y_LEN - 1)
	{//bottom left of the board
		btm_left  = -1;
		bottom    = -1;
		btm_right = -1;
		left      = -1;
		top_left  = -1;
	}
	else if (player->pos_x == BOARD_X_LEN - 1  && player->pos_y == BOARD_Y_LEN - 1)
	{//bottom right of the board
		btm_left  = -1;
		bottom    = -1;
		btm_right = -1;
		right     = -1;
		top_right = -1;
	}
	else if (player->pos_y == 0)
	{//top bar except corners
		top_left  = -1;
		top       = -1;
		top_right = -1;
	}
	else if (player->pos_y == BOARD_Y_LEN - 1)
	{//bottom bar execpt corners
		btm_left  = -1;
		bottom    = -1;
		btm_right = -1;
	}
	else if (player->pos_x == 0)
	{//left side of the board
		top_left = -1;
		left     = -1;
		btm_left = -1;
	}
	else if (player->pos_x == BOARD_X_LEN - 1)
	{//right side of the board
		top_right = -1;
		right     = -1;
		btm_right  = -1;
	}

	//fill remain position;
	if (top_left != -1)
		top_left = player->game->board[p_y - 1][p_x - 1];
	if (top != -1)
		top = player->game->board[p_y - 1][p_x];
	if (top_right != -1)
		top_right = player->game->board[p_y - 1][p_x + 1];
	if (left != -1)
		left = player->game->board[p_y][p_x - 1];
	if (right != -1)
		right = player->game->board[p_y][p_x + 1];
	if (btm_left != -1)
		btm_left = player->game->board[p_y + 1][p_x - 1];
	if (bottom != -1)
		bottom = player->game->board[p_y + 1][p_x];
	if (btm_right != -1)
		btm_right = player->game->board[p_y + 1][p_x + 1];
	//check if player died
	if (left > 0 && right > 0 && left != t_id && right != t_id)
		return (-1);
	if (top > 0 && bottom > 0 && top != t_id && bottom != t_id)
		return (-1);
	//check if player need to escape
	if (top > 0 && top != t_id &&
		((btm_left != t_id && btm_left > 0) || (btm_right != t_id && btm_right > 0)))
	{
			return (1);
	}
	if (right > 0 && right != t_id &&
		((top_left != t_id && top_left > 0) || (btm_left != t_id && btm_left > 0)))
	{
			return (1);
	}
	if (bottom > 0 && bottom != t_id &&
		((top_left != t_id && top_left > 0) || (top_right != t_id && top_right > 0)))
	{
			return (1);
	}
	if (left > 0 && left != t_id &&
		((top_right != t_id && top_right > 0) || (btm_right != t_id && btm_right > 0)))
	{
			return (1);
	}
	return (0);
}
