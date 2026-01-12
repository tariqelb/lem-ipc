#include "./lemipc.h"

int	ft_check_attack_sides_of_surrouned_enemy_and_choose_one(t_player *player, t_message_queue *msg)
{
	printf("ft_check_attack_sides_of_surrouned_enemy_and_choose_one\n");
	int	i;
	int	move;
	int	pos;

	move = 0;
	i = 0;
	while (i < 4 && move == 0) 
	{
		if (msg->sides[i] == 1)
		{
			pos = ft_is_it_one_step_to_position_x_y(player, msg->x_y_sides[i][0], msg->x_y_sides[i][1]);

			if (pos == 0)
				move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			if (move == 0 && pos == 1)
				move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			if (move == 0 && pos == 2)
				move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			if (move == 0 && pos == 3)
				move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
		}
		i++;
	}

	return (move);
}
