#include "./lemipc.h"


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

int	ft_attack_defend_escape_moves(t_player *player, t_message_queue *old_msg)
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
	//defence flag == 2 : x and y is position of enemy you should chose a side to attack [0]([E])[0]
	//defence flag == 4 : x and y is position of free place of surrounded enemy [p][E]([0])
	if (ft_player_first_checks_and_moves(player, old_msg))
		return (0);

	{
		move = 0;
		ft_get_target_enemy_team_id(player);
		msg_status = ft_get_message_from_message_queue(player, &msg);
		if (msg_status != 0)
		{
			msg_status = ft_calculate_push_new_attack(player, &new_msg);
			*old_msg = new_msg;
			if (msg_status == 0)
			{
				if (new_msg.defence_flag == 4)
				{
					move = ft_attack_position(player, new_msg.x_defence, new_msg.y_defence);
				}
				else
				{
					move = ft_second_side_to_attack(player, new_msg);
				}
				if (move == 0)
					printf("Attack one side surrouned enemy not complete\n");
				else
					printf("Attack one side surrouned enemy\n");
			}
			if (move)
				return (0);
		}
		else
		{
			//check if enemy still in position 
			if (ft_is_enemy_still_in_position(player, msg.x_attack, msg.y_attack) == 0)
			{
				msg_status = ft_calculate_push_new_attack(player, &msg);
				*old_msg = msg;
			}
			else
				ft_push_message_to_queue(player, &msg);
			if (msg_status == 0)
			{
				if (msg.defence_flag == 4)
					move = ft_attack_position(player, msg.x_defence, msg.y_defence);
				else
					move = ft_second_side_to_attack(player, msg);		
				printf("Player do move [%d] \n", move);
			}
			if (move == 0)
				printf("player change place\n");
		}
		
	}
	return (0);
}
