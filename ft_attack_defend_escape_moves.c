#include "./lemipc.h"

int	ft_get_message_from_message_queue(t_player *player, t_message_queue *msg)
{
	size_t size;
	int ret;

	// Add null check for safety
	if (!msg) 
		return (1);
	// msgrcv expects size without mtype
	size = sizeof(t_message_queue) - sizeof(long);
	ret = msgrcv(player->msqid, msg, size, player->team_id, IPC_NOWAIT);

	if (ret == -1)
		return (1);

	return (0);
}

int	ft_player_died(t_player *player)
{
	int	team_array_index;

	team_array_index = ft_get_team_array_index(player);
	printf("player surrouneded \n");
	if (team_array_index != -1)
	{
		player->game->teams[team_array_index].nbr_of_players--;	
		if (player->game->teams[team_array_index].nbr_of_players <= 0)
			player->game->total_teams--;
	}
	player->game->board[player->pos_y][player->pos_x] = 0;
	player->died = 1;
	return (1);
}

int	ft_first_move(t_player *player)
{
	//if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
	if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y - 1) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
		player->first_move = 0;
	}
	else if (ft_check_if_position_is_free(player, player->pos_x + 1, player->pos_y) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
		player->first_move = 0;
	}
	else if (ft_check_if_position_is_free(player, player->pos_x, player->pos_y + 1) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
		player->first_move = 0;
	}
	else if (ft_check_if_position_is_free(player, player->pos_x - 1, player->pos_y) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
		player->first_move = 0;
	}
	return (0);
}


int	ft_is_enemy_still_in_position(t_player *player, int x, int y)
{
	if (x >= 0 && y >= 0 && x < BOARD_X_LEN && y < BOARD_Y_LEN)
	{
		int position = player->game->board[y][x];

		if (position != 0 && position != player->team_id + 1)
		{
			return (1);
		}
		else 
			return (0);
	}
	return (0);
}

int	ft_attack_defend_escape_moves(t_player *player)
{
	//first get message from message queue if exist
	//check if your position need escape move
	//make some calculation for best move and compared with exist one
		//i need defend
		//team member need defend
		//attack the closet enemy
		//check if we win
	//if no message exist, then make calculation and push it to message queue
	//make you move
	t_message_queue msg;
	t_message_queue new_msg;
	int		msg_status;
	int		escape;
	int		move;
	//int		defence;
	//int		team_array_index;

	player->path[0] = -1;
	player->path[1] = -1;
	player->path[2] = -1;
	player->path[3] = -1;
	//team_array_index = ft_get_team_array_index(player);
	//-1 player died, 1 escape needed, 0 safe position
	//position (0,0), (0,31), (31,0), (31,31) is not strictly forbiden 
	//in escape case , allowed only in attack and player 
	//should not stay there
	//or in generale escape case not allowed in board sides

	//I decide to make corners (0,0), (0,31), (31,0) (31,31)
	//a place where player will died if he stay there 3 turn
	//each time he get semaphore and check if he is on corcer
	//if yes reduce one from player->corner variale till reach
	//0 then died, like that the game alyaws reach an end with a
	//team winner, cause i player on the corner can not be surrounded
	//the corner variable itself will increase each time a new player
	//from the same team gets in , the corner variable is team variable
	//that related to nbr of team member and decrease each time player
	//from the team go to corner
	//
	if (player->first_move)
	{
		//move on from the side to let other player get in the board
		printf("ft_first_move\n");
		ft_first_move(player);
		escape = ft_check_if_player_need_to_escape_or_died(player);
		if (escape == -1) //player surrounded
		{
			player->died = 1;
			printf("Player surrounded\n");
			return (1);
		}
		return (0);
	}
	/*if (ft_check_if_player_in_the_corner(player) == -1)
	{
		return (ft_player_died(player));
	}*/
	escape = ft_check_if_player_need_to_escape_or_died(player);
	if (escape == -1) //player surrounded
	{
		player->died = 1;
		//return (ft_player_died(player));
		printf("Player surrounded\n");
		return (1);
	}
	//check if i surround an enemy stay here
	if (ft_scan_board_if_a_player_surrounded(player))
	{
		printf("ft_scan_the_board_and_get_x_y_of_enemy_to_attack\n");
		printf("*********************************************\n");
		printf("*********************************************\n");
		printf("*********************************************\n");
		ft_print_the_board(player);
		printf("*********************************************\n");
		printf("*********************************************\n");
		printf("*********************************************\n");
		return (0);
	}
/*	if (ft_check_if_player_in_right_position_do_not_move(player))
	{
		printf("player in attack position no need to move\n");
		return (0);
	}*/
	//check if you are last player or escape == 1 mean you are in denger
	// just escape 
	/*if (escape == 1 || player->game->teams[team_array_index].nbr_of_players == 1)
	{
		printf("Under attack or Last player escape \n");
		ft_last_player_escape(player);
		return (0);
	}
	//to improve this we will push only attack message 
	//player by itself check if player need defence and move to defence before do an attack
	//msg_status = ft_get_message_from_message_queue(player, &msg);
	defence = ft_check_if_team_member_need_defence(player, &new_msg);
	if (defence == 1)
	{
		//(only first move should be safe)
		//move to defence position 
		ft_find_path_to_position_and_make_move(player, new_msg.x_defence, new_msg.y_defence);
		return (0);
	}
	else*/	
	{
		int	x,y;
		//best move ex. [p][0][E][P] move to right is best move
		int move = ft_best_move(player, &x, &y);
		if (move != -1)
		{
			printf("ft_easy_best_move\n");
			ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			return (0);
		}
	}
	{
		//second best move [0][P][0]
		//                 [0][E][0]
		//                 [p][0][0] move to right is second best move 
		int	x, y;
		int	move = ft_second_best_move(player, &x, &y);
		if (move != -1)
		{
			printf("ft_second_best_move\n");
			ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			return (0);
		}
	}
	{
		int	x, y;
		int	move = ft_move_to_best_position(player, &x, &y);
		if (move)
		{
			printf("ft_best_position\n");
			ft_move_to_position_x_y(player, player->pos_x + x, player->pos_y + y);
			return (0);

		}
	}
	{
		//update this section and test just accounce an attack if player surround enemy from one side 
		//player how surround enemy stay his place and others attack position
		//otherwise move closer
		ft_get_target_enemy_team_id(player);
		msg_status = ft_get_message_from_message_queue(player, &msg);
		if (msg.defence_flag != 4 && ft_check_if_player_surround_enemy_from_one_side(player, &msg))
		{
			printf("player surround enemy from one side\n");
			return (0);
		}
		move = 0;
		if (msg_status != 0)
		{
			msg_status = ft_calculate_push_new_attack(player, &new_msg);
			if (msg_status == 0)
			{
				if (new_msg.defence_flag == 2)
				{
					printf("Defence = 2\n");
				       	move = ft_check_attack_sides_of_surrouned_enemy_and_choose_one(player, &new_msg);
					if (move == 0)
					{
						int	i;

						i = 0;
						while (i < 4 && move == 0)
						{
							//check if enemy still in position
							move = ft_surround_side_to_attack(player, new_msg);
							i++;
						}
					}
				}
				if (move == 0)
					printf("Attack one side surrouned enemy not complete\n");
				else
					printf("Attack one side surrouned enemy\n");
			}
		}
		if (msg_status == 0 && move == 0)
		{
			//check if enemy still in position 
			if (ft_is_enemy_still_in_position(player, msg.x_attack, msg.y_attack))
			{
				move = ft_side_to_attack(player, msg);		
				msg_status = ft_calculate_push_new_attack(player, &new_msg);
				printf("Player do move [%d] \n", move);
			}
			if (move == 0) 
			{
				msg_status = ft_calculate_push_new_attack(player, &new_msg);
				if (msg_status == 0 && ft_is_enemy_still_in_position(player, new_msg.x_attack, new_msg.y_attack))
				{
					move = ft_side_to_attack(player, new_msg);		
					printf("Player do move [%d] \n", move);
				}
			}
			if (move == 0)
				printf("player change place\n");
		}
		
	}
	return (0);
}
