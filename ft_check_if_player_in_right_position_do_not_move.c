#include "./lemipc.h"


int	ft_check_if_player_in_right_position_do_not_move(t_player *player)
{
	int	p_top;
	int	p_right;
	int	p_bottom;
	int	p_left;


	//here i check if one of the sides of the player have a target enemy       0 0 0 
	//if yes the check other opposite side of the enemy if is a free place     P E 0
	//if yes just stay there and let other team members fill it                0 0 0

	if (player->target_team_id == -1)
		return (0);

	if (player->pos_x == 0)
		p_left = -1;
	else
		p_left = player->game->board[player->pos_y][player->pos_x - 1];

	if (player->pos_x == BOARD_X_LEN)
		p_right = -1;
	else
		p_right = player->game->board[player->pos_y][player->pos_x + 1];

	if (player->pos_y == 0)
		p_top = -1;
	else
		p_top = player->game->board[player->pos_y - 1][player->pos_x];

	if (player->pos_y == BOARD_Y_LEN)
		p_bottom = -1;
	else
		p_bottom = player->game->board[player->pos_y + 1][player->pos_x];

	if (p_top != -1 && p_top == player->target_team_id + 1)
	{
		int	p_top_top;

		p_top_top = player->pos_y - 2;
		if (p_top_top >= 0 && player->game->board[p_top_top][player->pos_x] == 0)
		{
			printf("block : p_x [%d] p_y [%d] : target [%d] ", player->pos_x, player->pos_y, player->target_team_id);
			printf("block : top p [%d], top top p [%d] \n", player->game->board[player->pos_y - 1][player->pos_x], player->game->board[player->pos_y - 2][player->pos_x]);
			return (1);
		}
	}
	if (p_right != -1 && p_right == player->target_team_id + 1)
	{
		int	p_right_right;

		p_right_right = player->pos_x + 2;
		if (p_right_right < BOARD_X_LEN && player->game->board[player->pos_y][p_right_right] == 0)
		{
			printf("block : p_x [%d] p_y [%d] : target [%d] ", player->pos_x, player->pos_y, player->target_team_id);
			printf("block : right p [%d], right right p [%d] \n", player->game->board[player->pos_y][player->pos_x + 1], player->game->board[player->pos_y][player->pos_x + 2]);
			return (1);
		}
	}
	if (p_bottom != -1 && p_bottom == player->target_team_id + 1)
	{
		int	p_bottom_bottom;

		p_bottom_bottom = player->pos_y + 2;
		if (p_bottom_bottom < BOARD_Y_LEN && player->game->board[p_bottom_bottom][player->pos_x] == 0)
		{
			printf("block : p_x [%d] p_y [%d] : target [%d] ", player->pos_x, player->pos_y, player->target_team_id);
			printf("block : btm p [%d], btm top p [%d] \n", player->game->board[player->pos_y + 1][player->pos_x], player->game->board[player->pos_y + 2][player->pos_x]);
			return (1);
		}
	}
	if (p_left != -1 && p_left == player->target_team_id + 1)
	{
		int	p_left_left;

		p_left_left = player->pos_x - 2;
		if (p_left_left >= 0 && player->game->board[player->pos_y][p_left_left] == 0)
		{
			printf("block : p_x [%d] p_y [%d] : target [%d] ", player->pos_x, player->pos_y, player->target_team_id);
			printf("block : left p [%d], left left p [%d] \n", player->game->board[player->pos_y][player->pos_x - 1], player->game->board[player->pos_y][player->pos_x - 2]);
			return (1);
		}
	}
	return (0);
}
