#include "./lemipc.h"

int	ft_player_first_checks_and_moves(t_player *player, t_message_queue *old_msg)
{
	printf("ft_player_first_checks_and_moves\n");
	int		move;
	int		last_attack;

	last_attack = 0;

	{
		//this use last announce msg
		//2 mean current player surrent enemy and its the player who aanounce the attack
		//return 3 if last attack still valid but enemy not surrouneded from any side
		last_attack = ft_check_if_attack_position_still_valid_and_free(player, old_msg);
		printf("last attack result : %d\n", last_attack);
		if (last_attack == 2)
		{
			printf("Player surround enemy first check\n");
			return (1);
		}
		if (last_attack == 0 && ft_check_if_player_surround_enemy_from_one_side(player, old_msg) > 0)
		{
			printf("Player surround enemy second check\n");
			return (1);
		}
	}
	{
		int	x,y;
		//best move ex. [p][0][E][P] move to right is best move
		int move = ft_best_move(player, &x, &y);
		if (move != -1)
		{
			printf("ft_easy_best_move\n");
			move = !ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			if (move)
				return (1);
		}
	}
	{
		//second best move [0][P][0]
		//                 [0][E][0]
		//                 [p][0][0] move to right is second best move
		int	x, y;
		int	move = ft_second_best_move(player, &x, &y);
		printf("ft_second_best_move [%d] \n", move);
		if (move != -1)
		{
			printf("ft_second_best_move\n");
			move = !ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			if (move)
				return (1);
		}
	}
	{
		//best position
		int	x, y;
		int	move = ft_move_to_best_position(player, &x, &y);
		if (move)
		{
			printf("ft_best_position\n");
			move = !ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			if (move)
				return (1);

		}
	}
	{
		printf("best second move\n");
		//best second move
		int	x, y;
		int	move = ft_move_to_second_best_position(player, &x, &y);

		if (move)
		{
			printf("best second position\n");
			move = !ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			if (move)
				return (1);
		}
	}
	{
		move = 0;
		//last_attack: 1 if last attack message still valid and 2 if current player who is announce it and 0 if not valid
		if (last_attack == 1)
		{
			//for message flag == 4
			//we will use x_attack and y_attack to save position of enemy and x_defence and y_defence  to save position to fill
			//x_player and y_player save the position of team member that surround enemy from one side and announce the attack
			printf("last attack == 1, ft_attack_position\n");
			move = ft_attack_position(player, old_msg->x_defence, old_msg->y_defence);
			if (move)
				return (1);
		}
		else if (last_attack == 0)
		{
			//check if current player surround enemy and announce an attack message if yes
			//this not use data on old msg just save new date on it and push  if player surround enemy
			
			//here you should confirm that no player from the same team surround an enemy
			if (ft_check_if_player_surround_enemy_from_one_side(player, old_msg) > 0)//push also message to queue
			{
				printf("player already surround enemy\n");
				return (1);
			}
		}
	}
	return (0);

}
