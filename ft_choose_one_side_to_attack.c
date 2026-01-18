#include "./lemipc.h"

int	ft_choose_one_side_to_attack(t_player *player, int x, int y)
{
	ft_putstr("ft_choose_one_side_to_attack\n");
	int	top_side;
	int	right_side;
	int	bottom_side;
	int	left_side;
	int	enemy_id;

	top_side = -1;
	right_side = -1;
	bottom_side = -1;
	left_side = -1;

	if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
		return (-1);

	if (x > 0)
		left_side = player->game->board[y][x - 1];
	if (x < BOARD_X_LEN - 1)
		right_side = player->game->board[y][x + 1];
	if (y > 0)
		top_side = player->game->board[y - 1][x];
	if (y < BOARD_Y_LEN - 1)
		bottom_side = player->game->board[y + 1][x];
	enemy_id = -1;
	if (x >= 0 && x < BOARD_X_LEN && y >= 0 && y < BOARD_Y_LEN && player->game->board[y][x] != 0)
		enemy_id = player->game->board[y][x];

	if (enemy_id == -1)
		return (-1);
	if (bottom_side > 0 && bottom_side != enemy_id && top_side == 0)
		return (0);
	if (left_side > 0 && left_side != enemy_id && right_side == 0)
		return (1);
	if (top_side > 0 && top_side != enemy_id && bottom_side == 0)
		return (2);
	if (right_side > 0 && right_side != enemy_id && left_side == 0)
		return (3);


	if (player->pos_x > x && player->pos_y > y)//enemy on left top side
	{
		if (bottom_side == 0 && player->pos_y - y > 1)
			return (2);
		if (right_side == 0 && player->pos_x - x > 1)
			return (1);
	}
	if (player->pos_x == x && player->pos_y > y)//enemy on top side
	{
		if (bottom_side == 0 && player->pos_y - y > 1)
			return (2);
	}
	if (player->pos_x < x && player->pos_y > y)//enemy on top right side
	{
		if (left_side == 0 && x - player->pos_x > 1)
			return (3);
		if (bottom_side == 0 && player->pos_y - y > 1)
			return (2);
	}
	if (player->pos_x < x && player->pos_y == y)//enemy on right side
	{
		if (left_side == 0 && x - player->pos_x > 1)
			return (3);
	}
	if (player->pos_x < x && player->pos_y < y)//enemy on bottom right side
	{
		if (top_side == 0 && x - player->pos_x > 1)
			return (0);
		if (left_side == 0 && y - player->pos_y > 1)
			return (3);
	}
	if (player->pos_x == x && player->pos_y < y)//enemy on bottom side
	{
		if (top_side == 0 && y - player->pos_y > 1)
			return (0);
	}
	if (player->pos_x < x && player->pos_y < y)//enemy on bottom left side
	{
		if (right_side == 0 && x - player->pos_x > 1)
			return (1);
		if (top_side == 0 && y - player->pos_y > 1)
			return (0);
	}
	if (player->pos_x > x && player->pos_y == y)//enemy on left side
	{
		if (right_side == 0 && player->pos_x - x > 1)
			return (1);
	}
	return (-1);
}
