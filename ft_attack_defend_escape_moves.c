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
	if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
		player->first_move = 0;
	}
	else if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
		player->first_move = 0;
	}
	else if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
		player->first_move = 0;
	}
	else if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
	{
		ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
		player->first_move = 0;
	}
	return (0);
}

int	ft_side_to_attack(t_player *player, t_message_queue msg)
{
	printf("side to attack\n");

	int side_to_attack = -1;//top=0,right=1,bottom=2,left=3
	//if no valid path to one of the 4 sides of attack position, then return -1
	side_to_attack = ft_choose_one_side_to_attack(player, msg.x_attack, msg.y_attack);
	if (side_to_attack != -1)
	{
		if (ft_is_it_one_step_to_position(player, msg, side_to_attack) > 0)
		{
			printf("is one step to side to attacki [%d]\n", side_to_attack);
			//check if its safe and move
			if (side_to_attack == 0)
			{
				if (ft_check_position_is_safe(player, player->pos_x, player->pos_y - 1) == 0)
					ft_move_to_position_x_y(player, player->pos_x, player->pos_y - 1);
			}
			else if (side_to_attack == 1)
			{
				if (ft_check_position_is_safe(player, player->pos_x + 1, player->pos_y) == 0)
					ft_move_to_position_x_y(player, player->pos_x + 1, player->pos_y);
			}
			else if (side_to_attack == 2)
			{
				if (ft_check_position_is_safe(player, player->pos_x, player->pos_y + 1) == 0)
					ft_move_to_position_x_y(player, player->pos_x, player->pos_y + 1);
			}
			else if (side_to_attack == 3)
			{
				if (ft_check_position_is_safe(player, player->pos_x - 1, player->pos_y) == 0)
					ft_move_to_position_x_y(player, player->pos_x - 1, player->pos_y);
			}
		}
		else
		{//find path to one of the sides in attack msg and move to it
		 	int move = 0;//move == 0 mean player can attack position
			printf("find path side to attack [%d]\n", side_to_attack);
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
			if (move == 0)
			{//check other side to attack
				if (player->path[0] != -1 && side_to_attack != 0)
					move = ft_find_path_to_position_and_make_move(player, msg.x_attack, msg.y_attack - 1);	
				if (move == 0 && player->path[1] != -1 && side_to_attack != 1)
					move = ft_find_path_to_position_and_make_move(player, msg.x_attack + 1, msg.y_attack);	
				if (move == 0 && player->path[2] != -1 && side_to_attack != 2)
					move = ft_find_path_to_position_and_make_move(player, msg.x_attack, msg.y_attack + 1);	
				if (move == 0 && player->path[3] != -1 && side_to_attack != 3)
					move = ft_find_path_to_position_and_make_move(player, msg.x_attack - 1, msg.y_attack);	
			}
			return (move);
		}
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
	int		defence;
	int		team_array_index;

	player->path[0] = -1;
	player->path[1] = -1;
	player->path[2] = -1;
	player->path[3] = -1;
	team_array_index = ft_get_team_array_index(player);
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
		ft_first_move(player);
		return (0);
	}
	/*if (ft_check_if_player_in_the_corner(player) == -1)
	{
		return (ft_player_died(player));
	}*/
	escape = ft_check_if_player_need_to_escape_or_died(player);
	printf("Escape : %d\n", escape);
	if (escape == -1) //player surrounded
	{
		return (ft_player_died(player));
	}
	if (ft_check_if_player_in_right_position_do_not_move(player))
	{
		printf("player in attack position no need to move\n");
		return (0);
	}
	//check if you are last player or escape == 1 mean you are in denger
	// just escape 
	if (escape == 1 || player->game->teams[team_array_index].nbr_of_players == 1)
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
		printf("Defence = 1 [%d] \n", defence);
		//(only first move should be safe)
		//move to defence position 
		ft_find_path_to_position_and_make_move(player, new_msg.x_defence, new_msg.y_defence);
		return (0);
	}
	else	
	{
		//do attack move
		///attack position should be 4 for team members more than 4
		// 3 position for team of 3 players and 2 for team of 2
		//so message queue struct should be updated for that 
		//also the position of the enemy i want to attack
		//other player check if enemy still there if yes just move
		//otherwise check for colest enemy and do new calculation
		//and push new message 

		///i think is better to leave it one position of the attacked enemy
		//then if enemy exist in this position attack one of its side otherwise 
		//do other calculation and push message 
		
		//choose target enemy team , return target id
		ft_get_target_enemy_team_id(player);

		//if no message exist calculate new one
		msg_status = ft_get_message_from_message_queue(player, &msg);
		if (msg_status != 0 || (msg_status == 0 && (player->game->board[msg.x_attack][msg.y_attack] == 0 || player->game->board[msg.x_attack][msg.y_attack] == player->team_id - 1)))
		{
			msg_status = ft_calculate_push_new_attack(player, &new_msg);
			printf("old attack [%d][%d]\n", msg.x_attack, msg.y_attack);
			msg = new_msg;
			printf("Board enemy x y [%d] target [%d]\n", player->game->board[new_msg.y_attack][new_msg.x_attack], player->target_team_id);
			printf("calculate new attack [%d][%d]\n", new_msg.x_attack, new_msg.y_attack);
			printf("update attack [%d][%d]\n", msg.x_attack, msg.y_attack);
			if (msg.x_attack < BOARD_X_LEN && msg.y_attack < BOARD_Y_LEN
				&& player->game->board[msg.y_attack][msg.x_attack] != 0
				&& player->game->board[msg.y_attack][msg.x_attack] != player->team_id - 1)
			{
				int move;
				move = ft_side_to_attack(player, msg);		
				printf("Player do move [%d] \n", move);
			}
			else 
				printf("player change place\n");
		}
		else if (msg_status == 0)
		{
			printf("Attack , msg status [%d] tagert [%d] \n", msg_status, player->target_team_id);
			printf("Attack x y board [%d][%d][%d]\n", msg.x_attack, msg.y_attack, player->game->board[msg.x_attack][msg.y_attack]);
			//check if enemy still in position 
			if (msg.x_attack < BOARD_X_LEN && msg.y_attack < BOARD_Y_LEN
				&& player->game->board[msg.y_attack][msg.x_attack] != 0
				&& player->game->board[msg.y_attack][msg.x_attack] != player->team_id - 1)
			{
				int move;
				move = ft_side_to_attack(player, msg);		
				printf("Player do move [%d] \n", move);
			}
			else 
				printf("player change place\n");
			msg_status = ft_calculate_push_new_attack(player, &new_msg);
		}
		
	}
	return (0);
}
