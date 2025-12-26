#include "./lemipc.h"

int	ft_check_if_postion_need_defence(t_player *player, int p_x, int p_y, t_message_queue *new_msg)
{
	int	top_left;
	int	top_right;
	int	btm_left;
	int	btm_right;
	int	top;
	int	right;
	int	bottom;
	int	left;
	int	t_id;

	top_left  = 0;
	top_right = 0;
	btm_left  = 0;
	btm_right = 0;
	top       = 0;
	right     = 0;
	bottom    = 0;
	left      = 0;
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
		new_msg->defence_flag = 1;
		new_msg->team_id = player->team_id;
		new_msg->y_defence = p_y - 1;
		if (btm_left != t_id && btm_left > 0)
			new_msg->x_defence = p_x - 1;
		else if (btm_right != t_id && btm_right > 0)
			new_msg->x_defence = p_x + 1;
		return (1);
	}
	if (right > 0 && right != t_id &&
		((top_left != t_id && top_left > 0) || (btm_left != t_id && btm_left > 0)))
	{
		new_msg->defence_flag = 1;
		new_msg->x_defence = p_x - 1;
		if (top_left != t_id && top_left > 0)
			new_msg->y_defence = p_y - 1;
		else if (btm_left != t_id && btm_left > 0)
			new_msg->y_defence = p_y + 1;
		return (1);
	}
	if (bottom > 0 && bottom != t_id &&
		((top_left != t_id && top_left > 0) || (top_right != t_id && top_right > 0)))
	{
		new_msg->defence_flag = 1;
		new_msg->y_defence = p_y + 1;
		if (top_left != t_id && top_left > 0)
			new_msg->x_defence = p_x - 1;
		else if (top_right != t_id && top_right > 0)
			new_msg->x_defence = p_x + 1;
		return (1);
	}
	if (left > 0 && left != t_id &&
		((top_right != t_id && top_right > 0) || (btm_right != t_id && btm_right > 0)))
	{
		new_msg->defence_flag = 1;
		new_msg->x_defence = p_x + 1;
		if (top_left != t_id && top_left > 0)
			new_msg->y_defence = p_y - 1;
		else if (btm_left != t_id && btm_left > 0)
			new_msg->y_defence = p_y + 1;
		return (1);
	}
	return (0);
}

int	 ft_check_if_team_member_need_defence(t_player *player, t_message_queue *new_msg)
{
	int	checked_player;
	int	team_array_index;
	//scan board x and y is and index where i reach so i complete 
	//the scan from this point after check player is need defence 
	int	i_x;
	int	i_y;
	int	defence;
	int	nbr_of_player;

	defence = 0;
	team_array_index = ft_get_team_array_index(player);
	if (team_array_index)
		return (0);
	nbr_of_player = player->game->teams[team_array_index].nbr_of_players;
	checked_player = 0;
	//scan the board and when you find a player from your team
	//check if this player need defence if yes save position need defence
	//otherwise move to next player
	i_y = 0;
	while (i_y < BOARD_Y_LEN && checked_player < nbr_of_player)
	{
		i_x = 0;
		while (i_x < BOARD_X_LEN)
		{
			if (player->game->board[i_y][i_x] == player->team_id + 1)
			{
				defence = ft_check_if_postion_need_defence(player, i_x, i_y, new_msg);	
				if (defence == 1)
				{
					return (1);
				}
				else
					checked_player++;
			}
			i_x++;
		}
		i_y++;
	}

	return (defence);
}
