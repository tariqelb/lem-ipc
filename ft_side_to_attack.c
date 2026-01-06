#include "./lemipc.h"

int	ft_side_to_attack(t_player *player, t_message_queue msg)
{
	printf("ft_side_to_attack\n");

	int side_to_attack = -1;//top=0,right=1,bottom=2,left=3
	int	move;

	move = 0;
	//if no valid path to one of the 4 sides of attack position, then return -1
	side_to_attack = ft_choose_one_side_to_attack(player, msg.x_attack, msg.y_attack);
	if (side_to_attack != -1)
	{
		int enemy_side = ft_is_it_one_step_to_position(player, msg, side_to_attack);
		if (enemy_side >= 0)
		{
			printf("ft_is_it_one_step_to_position\n");
			//check if its safe and move
			if (enemy_side == 0)
			{
				//if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
				if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			}
			else if (enemy_side == 1)
			{
				if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			}
			else if (enemy_side == 2)
			{
				if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			}
			else if (enemy_side == 3)
			{
				if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0)
					move = !ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
			}
		}
		else
		{//find path to one of the sides in attack msg and move to it
		 	//move == 0 mean player can attack position
			if (side_to_attack == 0)//top
			{
				move = ft_find_path_to_position_and_make_move(player, msg.x_attack, msg.y_attack - 1);	
			}
			else if (side_to_attack == 1)//right
			{
				move = ft_find_path_to_position_and_make_move(player, msg.x_attack + 1, msg.y_attack);	
			}
			else if (side_to_attack == 2)//bottom
			{
				move = ft_find_path_to_position_and_make_move(player, msg.x_attack, msg.y_attack + 1);	
			}
			else if (side_to_attack == 3)//left
			{
				move = ft_find_path_to_position_and_make_move(player, msg.x_attack - 1, msg.y_attack);	
			}
			printf("ft_find_path.... move[%d]\n", move);
		}
	}
	printf("move [%d]\n", move);
	if (move == 0)
		move = ft_find_best_move_and_escape(player);
	printf("move [%d]\n", move);
	return (move);
}


int	ft_surround_side_to_attack(t_player *player, t_message_queue msg)
{
	printf("ft_surround_side_to_attack\n");

	int	move;
	int	i;

	move = 0;
	i = 0;
	while (i < 4 && move == 0)
	{
		if (msg.sides[i] == 1)
			move = ft_find_path_to_position_and_make_move(player, msg.x_y_sides[i][0], msg.x_y_sides[i][1]);
		if (move)
			printf("ft_find_path.... move [%d] side [%d]\n", move, msg.sides[i]);
		i++;
	}
	printf("move [%d]\n", move);
	if (move == 0)
		move = ft_find_best_move_and_escape(player);
	printf("move [%d]\n", move);
	return (move);
}

