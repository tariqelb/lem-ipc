#include "./lemipc.h"

int	ft_attack_position(t_player *player, int x, int y)
{
	ft_putstr("ft_attack_position\n");
	int	one_step;
	int	move ;

	//ft_putstr("ft_attack_position enemy x [%d] y [%d]\n", x, y);
	move = 0;

	if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
		return (0);
	one_step = ft_is_it_one_step_to_position_x_y(player, x, y);
	if (one_step >= 0)
	{
		move = !ft_move_to_position_x_y(player, x, y);
	}
	else
	{
 		move = ft_find_path_to_position_and_make_move(player, x, y);
	}
	return (move);
}

int	ft_second_side_to_attack(t_player *player, t_message_queue msg)
{
	ft_putstr("ft_surround_side_to_attack\n");

	int	move;
	int	x_attack;
	int	y_attack;
	int	one_step;

	if (msg.defence_flag == 4)
	{
		x_attack = msg.x_defence;
		y_attack = msg.y_defence;
	}
	else 
	{
		x_attack = msg.x_attack;
		y_attack = msg.y_attack;
	}

	move = 0;
	one_step = ft_is_it_one_step_to_position_x_y(player, x_attack, y_attack);
	if (one_step >= 0)
	{

			if (one_step == 0)
			{
				//if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
				if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			}
			else if (one_step == 1)
			{
				if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			}
			else if (one_step == 2)
			{
				if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			}
			else if (one_step == 3)
			{
				if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
			}
			if (move)
				return (1);

	}

	move = ft_find_path_to_position_and_make_move(player, x_attack , y_attack);
	return (move);
}

