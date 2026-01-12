#include "./lemipc.h"

int     ft_is_it_one_step_to_position_x_y(t_player *player, int x, int y)
{
        printf("ft_is_it_one_step_to_position_x_y\n");
	printf("Data p_x[%d] p_y[%d] x[%d] y[%d] \n", player->pos_x, player->pos_y, x, y);

        if (x < 0 || x >= BOARD_X_LEN || y < 0 || y >= BOARD_Y_LEN)
                return (-1);
        if (player->pos_y - 1 == y && player->pos_x == x)
                return (0);
        if (player->pos_x + 1 && player->pos_y == y)
                return (1);
        if (player->pos_y + 1 == y && player->pos_x == x)
                return (2);
        if (player->pos_x - 1 == x && player->pos_y == y)
                return (3);
        return (-1);
}


int	ft_is_it_one_step_to_position(t_player *player, t_message_queue msg, int side_to_attack)
{
	int	attack_x;
	int	attack_y;

	printf("ft_is_it_one_step_to_position\n");
	//the msg attack hold cooredinate of the position to attack
	//the ft_choose_side_to_attack() function return best side to attack
	//now we check is it one step to that side

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
	{
		printf("one side = 0\n");
		return (0);
	}
	else if (player->pos_x + 1 == attack_x && player->pos_y == attack_y)
	{
		printf("one side = 1\n");
		return (1);
	}
	else if (player->pos_x == attack_x && player->pos_y + 1 == attack_y)
	{
		printf("one side = 2\n");
		return (2);
	}
	else if (player->pos_x - 1 == attack_x && player->pos_y == attack_y)
	{
		printf("one side = 3\n");
		return (3);
	}
	printf("one side = -1\n");

	return (-1);
}
