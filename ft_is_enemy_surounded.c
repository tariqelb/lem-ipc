#include "./lemipc.h"

int	ft_is_player_surrounded(t_player *player)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;
	if (RANDOM)
	{
		return (ft_random_rule_check_if_player_surrounded(player, player->team_id + 1, player->pos_x, player->pos_y));
	}
	printf("Check is player surouneded [%d][%d]\n", player->pos_x, player->pos_y);
	ft_print_the_board(player);
	
	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];
	if (player->pos_x < BOARD_X_LEN - 1)
		right = player->game->board[player->pos_y][player->pos_x + 1];
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];

	printf("Data top[%d] pos[%d] btm[%d]\n", top, player->game->board[player->pos_y][player->pos_x], bottom);
	printf("Data left[%d] pos[%d] right[%d]\n", left, player->game->board[player->pos_y][player->pos_x], right);
	if (top > 0 && top != player->team_id + 1 && bottom > 0 && bottom != player->team_id + 1)
		return (1);

	if (left > 0 && left != player->team_id + 1 && right > 0 && right != player->team_id + 1)
		return (1);
	return (0);
}


int	ft_get_player_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left)
{
	if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
		return (1);
	
	*top = 0;
	*right = 0;
	*bottom = 0;
	*left = 0;

	if (x == 0)
		*left = -1;
	if (x == BOARD_X_LEN - 1)
		*right = -1;
	if (y == 0)
		*top = -1;
	if (y == BOARD_Y_LEN - 1)
		*bottom = -1;

	if (*top == 0)
		*top = player->game->board[y - 1][x];
	if (*right == 0)
		*right = player->game->board[y][x + 1];
	if (*bottom == 0)
		*bottom = player->game->board[y + 1][x];
	if (*left == 0)
		*left = player->game->board[y][x - 1];

	return (0);
}


int	ft_scan_board_if_a_player_surrounded(t_player *player)
{
	printf("ft_scan_board_if_a_player_surrounded\n");
	int	y;
	int	x;

	//scan board if player surronded , if yes no player should move till surrounded player leave the board

	y = 0;
	while (y < BOARD_Y_LEN)
	{
		x = 0;
		while (x < BOARD_X_LEN)
		{
			int top;
			int right;
			int bottom;
			int left;
			int curr_pos;

			curr_pos = player->game->board[y][x];
			if (curr_pos)
			{
				if (RANDOM)
				{
					if(ft_random_rule_check_if_player_surrounded(player, curr_pos, x, y))
						return (1);
				}
				else
				{
					ft_get_player_sides(player, x, y, &top, &right, &bottom, &left);
					//printf("scan board if enemy dead : top[%d]  curr[%d] btm[%d] x y [%d,%d]\n", top, curr_pos, bottom , x ,y);
					//printf("scan board if enemy dead : left[%d] curr[%d] right[%d]\n", left, curr_pos, right);
					if (left > 0 && right > 0 && left != curr_pos && right != curr_pos)
					{
						printf("ft_scan_if_a_player_surrounded left[%d] [%d] right[%d]\n", left, curr_pos, right);
						return (1);
					}
					if (top > 0 && bottom > 0 && top != curr_pos && bottom != curr_pos)
					{
						printf("ft_scan_if_a_player_surrounded top[%d] [%d] bottom[%d]\n", top, curr_pos, bottom);
						return (1);
					}
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}
