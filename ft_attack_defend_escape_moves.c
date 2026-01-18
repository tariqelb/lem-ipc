#include "./lemipc.h"

int	ft_player_died(t_player *player)
{
	ft_putstr("ft_player died \n");
	int	team_array_index;

	team_array_index = ft_get_team_array_index(player);
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
	ft_putstr("ft_attack_defence_escape_moves\n");
	t_message_queue msg;
	t_message_queue new_msg;
	int		msg_status;
	int		escape;
	int		move;

	player->path[0] = -1;
	player->path[1] = -1;
	player->path[2] = -1;
	player->path[3] = -1;

	if (player->first_move)
	{
		//move on from the side to let other player get in the board
		ft_first_move(player);
		escape = ft_check_if_player_need_to_escape_or_died(player);
		if (escape == -1) //player surrounded
		{
			player->died = 1;
			ft_putstr("Player surrounded\n");
			return (1);
		}
		return (0);
	}
	/*if (ft_check_if_player_in_the_corner(player) == -1)
	{
		//position (0,0), (0,31), (31,0), (31,31) is not strictly forbiden 
		//I decide to make corners (0,0), (0,31), (31,0) (31,31) in board of 32/32
		//a place where player will died if he stay there 3 turn
		//each time he get semaphore and check if he is on corcer
		//if yes reduce one from player->corner variale till reach
		//0 then died, like that the game alyaws reach an end with a
		//team winner, cause i player on the corner can not be surrounded
		//the corner variable itself will increase each time a new player
		//from the same team gets in , the corner variable is team variable
		//that related to nbr of team member and decrease each time player
		//from the team go to corner
		return (ft_player_died(player));
	}*/
	escape = ft_check_if_player_need_to_escape_or_died(player);
	if (escape == -1) //player surrounded
	{
		player->died = 1;
		ft_putstr("Player surrounded\n");
		return (1);
	}
	if (RANDOM == 0 && ft_player_first_checks_and_moves(player, old_msg))
		return (0);
	//check if i surround an enemy stay here
	if (ft_scan_board_if_a_player_surrounded(player))
	{
		ft_putstr("*********************************************\n");
		ft_print_the_board(player);
		ft_putstr("*********************************************\n");
		return (0);
	}

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
				if (RANDOM)
				{
					if (ft_random_rule_check_if_player_attacked_surround_enemy_from_side(player, new_msg.x_attack, new_msg.y_attack))
						return (0);
				}
				if (RANDOM == 0 && new_msg.defence_flag == 4)
				{
					move = ft_attack_position(player, new_msg.x_defence, new_msg.y_defence);
				}
				else
				{
					move = ft_second_side_to_attack(player, new_msg);
				}
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
				if (RANDOM)
				{
					if (ft_random_rule_check_if_player_attacked_surround_enemy_from_side(player, msg.x_attack, msg.y_attack))
						return (0);
				}
				if (RANDOM == 0 && msg.defence_flag == 4)
					move = ft_attack_position(player, msg.x_defence, msg.y_defence);
				else
					move = ft_second_side_to_attack(player, msg);		
			}
		}
		
	}
	return (0);
}
