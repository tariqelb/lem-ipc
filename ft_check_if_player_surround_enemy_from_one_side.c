#include "./lemipc.h"

int	ft_get_position_sides(t_player *player, int x, int y, int *top, int *right, int *bottom, int *left)
{
	printf("ft_get_position_sides\n");
	*top = -1;
	*right = -1;
	*bottom = -1;
	*left = -1;

	if (x >= 0 && x < BOARD_X_LEN && y - 1 >= 0 && y - 1 < BOARD_Y_LEN)
		*top = player->game->board[y - 1][x];
	if (x + 1 >= 0 && x + 1 < BOARD_X_LEN && y >= 0 && y < BOARD_Y_LEN)
		*right = player->game->board[y][x + 1];
	if (x >= 0 && x < BOARD_X_LEN && y + 1 >= 0 && y + 1 < BOARD_Y_LEN)
		*bottom = player->game->board[y + 1][x];
	if (x - 1 >= 0 && x - 1 < BOARD_X_LEN && y >= 0 && y < BOARD_Y_LEN)
		*left = player->game->board[y][x - 1];

	printf("x y [%d] [%d] sides t[%d]r[%d]b[%d]l[%d]\n", x, y, *top, *right, *bottom, *left);

	return (0);
}

int	ft_check_if_player_surround_enemy_from_one_side(t_player *player , t_message_queue *msg)
{
	printf("ft_check_if_player_surround_enemy_from_one_side\n");
	//this function check player side if enemy exist and next opposite free , just stay here
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
       
	if (top > 0 && top != player_id && top_top == 0)
	{
		int enemy_top_side;
		int enemy_right_side;
		int enemy_bottom_side;
		int enemy_left_side;
		ft_get_position_sides(player, player->pos_x, player->pos_y - 1, &enemy_top_side, &enemy_right_side, &enemy_bottom_side, &enemy_left_side);
		if (enemy_left_side != -1 && enemy_right_side != -1 && enemy_left_side != player->team_id + 1 && enemy_right_side != player->team_id + 1)
		{
			msg->x_player = player->pos_x;
			msg->y_player = player->pos_y;
			msg->x_attack = player->pos_x;
			msg->y_attack = player->pos_y - 1;
			msg->x_defence = player->pos_x;
			msg->y_attack = player->pos_y - 2;
			msg->defence_flag = 4;
			ft_push_message_to_queue(player, msg);
			printf("Top data [%d][%d][%d][%d][%d][%d]\n", msg->x_player, msg->y_player, msg->x_attack, msg->y_attack, msg->y_defence, msg->y_defence);
			return (1);
		}
	}
	if (right > 0 && right != player_id && right_right == 0)
	{
		int	    enemy_top_side;
		int	    enemy_right_side;
		int	    enemy_bottom_side;
		int	    enemy_left_side;
		ft_get_position_sides(player, player->pos_x + 1, player->pos_y, &enemy_top_side, &enemy_right_side, &enemy_bottom_side, &enemy_left_side);
		if (enemy_left_side != -1 && enemy_top_side != -1 && player->team_id + 1 && enemy_bottom_side != player->team_id + 1)
		{
			msg->x_player = player->pos_x;
			msg->y_player = player->pos_y;	
			msg->x_attack = player->pos_x + 1;
			msg->y_attack = player->pos_y;
			msg->x_defence = player->pos_x + 2;
			msg->y_defence = player->pos_y;
			msg->defence_flag = 4;
			ft_push_message_to_queue(player, msg);
			printf("Right data [%d][%d][%d][%d][%d][%d]\n", msg->x_player, msg->y_player, msg->x_attack, msg->y_attack, msg->y_defence, msg->y_defence);
			return (2);
		}
	}
	if (bottom > 0 && bottom != player_id && bottom_bottom == 0)
	{
		int enemy_top_side;
		int enemy_right_side;
		int enemy_bottom_side;
		int enemy_left_side;
		ft_get_position_sides(player, player->pos_x, player->pos_y - 1, &enemy_top_side, &enemy_right_side, &enemy_bottom_side, &enemy_left_side);
		if (enemy_left_side != -1 && enemy_right_side != -1 && enemy_left_side != player->team_id + 1 && enemy_right_side != player->team_id + 1)
		{
			msg->x_player = player->pos_x;
			msg->y_player = player->pos_y;
			msg->x_attack = player->pos_x;
			msg->y_attack = player->pos_y + 1;
			msg->x_defence = player->pos_x;
			msg->y_defence = player->pos_y + 2;
			msg->defence_flag = 4;
			ft_push_message_to_queue(player, msg);
			printf("Bottom data [%d][%d][%d][%d][%d][%d]\n", msg->x_player, msg->y_player, msg->x_attack, msg->y_attack, msg->y_defence, msg->y_defence);
			return (3);
		}
	}
	if (left > 0 && left != player_id && left_left == 0)
	{
		int enemy_top_side;
		int enemy_right_side;
		int enemy_bottom_side;
		int enemy_left_side;
		ft_get_position_sides(player, player->pos_x, player->pos_y - 1, &enemy_top_side, &enemy_right_side, &enemy_bottom_side, &enemy_left_side);
		if (enemy_left_side != -1 && enemy_top_side != -1 && player->team_id + 1 && enemy_bottom_side != player->team_id + 1)
		{
			msg->x_player = player->pos_x;
			msg->y_player = player->pos_y;
			msg->x_attack = player->pos_x - 1;
			msg->y_attack = player->pos_y;
			msg->x_defence = player->pos_x - 2;
			msg->y_defence = player->pos_y;
			msg->defence_flag = 4;
			ft_push_message_to_queue(player, msg);
			printf("Left data [%d][%d][%d][%d][%d][%d]\n", msg->x_player, msg->y_player, msg->x_attack, msg->y_attack, msg->y_defence, msg->y_defence);
			return (4);
		}
	}

	return (0);
}
