#include "./lemipc.h"

int	ft_player_surround_enemy_from_one_side_and_other_side_free(t_player *player, t_message_queue *msg)
{
	printf("ft_player_surround_enemy_from_one_side_and_other_side_free\n");
	int	top;
	int	right;
	int	bottom;
	int	left;
	int	player_id;
	int	top_top;
	int	right_right;
	int	bottom_bottom;
	int	left_left;

	top = -1;
	right = -1;
	bottom = -1;
	left = -1;
	
	top_top = -1;
	right_right = -1;
	bottom_bottom = -1;
	left_left = -1;

	player_id = player->team_id + 1;

	if (player->pos_x > 0)
		left = player->game->board[player->pos_y][player->pos_x - 1];	
	if (player->pos_x < BOARD_X_LEN - 1)
		right = player->game->board[player->pos_y][player->pos_x + 1];	
	if (player->pos_y > 0)
		top = player->game->board[player->pos_y - 1][player->pos_x];	
	if (player->pos_y < BOARD_Y_LEN - 1)
		bottom = player->game->board[player->pos_y + 1][player->pos_x];	
	
	if (player->pos_x > 1)
		left_left = player->game->board[player->pos_y][player->pos_x - 2];
	if (player->pos_x < BOARD_X_LEN - 2)
		right_right = player->game->board[player->pos_y][player->pos_x + 2];	
	if (player->pos_y > 1)
		top_top = player->game->board[player->pos_y - 2][player->pos_x];
	if (player->pos_y < BOARD_Y_LEN - 2)
		bottom_bottom = player->game->board[player->pos_y + 2][player->pos_x];

	msg->sides[0] = -1;
	msg->sides[1] = -1;
	msg->sides[2] = -1;
	msg->sides[3] = -1;

	if (top > 0 && top != player_id && top_top == 0)
	{
		msg->x_y_sides[0][0] = player->pos_x;
		msg->x_y_sides[0][1] = player->pos_y - 2;
		msg->defence_flag = 2;
		msg->sides[0] = 1;
		return (1);
	}
	if (right > 0 && right != player_id && right_right == 0)
	{
		msg->x_y_sides[1][0] = player->pos_x + 2;
		msg->x_y_sides[1][1] = player->pos_y;
		msg->defence_flag = 2;
		msg->sides[1] = 1;
		return (1);
	}
	if (bottom > 0 && bottom != player_id && bottom_bottom == 0)
	{
		msg->x_y_sides[2][0] = player->pos_x;
		msg->x_y_sides[2][1] = player->pos_y + 2;
		msg->defence_flag = 2;
		msg->sides[2] = 1;
		return (1);
	}
	if (left > 0 && left != player_id && left_left == 0)
	{
		msg->x_y_sides[3][0] = player->pos_x - 2;
		msg->x_y_sides[3][1] = player->pos_y;
		msg->defence_flag = 2;
		msg->sides[3] = 1;
		return (1);
	}
	return (0);
}
