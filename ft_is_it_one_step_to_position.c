#include "./lemipc.h"


int	ft_is_it_one_step_to_position(t_player *player, t_message_queue msg, int side_to_attack)
{
	int	attack_x;
	int	attack_y;

	//the msg attack hold cooredinate of the position to attack
	//the ft_choose_side_to_attack() function return best side to attack
	//now we check is it one step to that side

	//printf("Data : %d %d , %d %d, %d\n", player->pos_x, player->pos_y, msg.x_attack, msg.y_attack, side_to_attack);

	if (side_to_attack == 0)
	{
		attack_x = msg.x_attack;
		attack_y = msg.y_attack - 1;
	}
	else if (side_to_attack == 1)
	{
		attack_x = msg.x_attack + 1;
		attack_y = msg.y_attack;
	}
	else if (side_to_attack == 2)
	{
		attack_x = msg.x_attack;
		attack_y = msg.y_attack + 1;
	}
	else if (side_to_attack == 3)
	{
		attack_x = msg.x_attack - 1;
		attack_y = msg.y_attack;
	}

	if (player->pos_x == attack_x && player->pos_y - 1 == attack_y)
		return (0);
	else if (player->pos_x + 1 == attack_x && player->pos_y == attack_y)
		return (1);
	else if (player->pos_x == attack_x && player->pos_y + 1 == attack_y)
		return (2);
	else if (player->pos_x - 1 == attack_x && player->pos_y == attack_y)
		return (3);

	return (-1);
}
