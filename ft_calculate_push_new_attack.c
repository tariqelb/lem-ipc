#include "./lemipc.h"

int	ft_calculate_push_new_attack(t_player *player, t_message_queue *msg)
{
	printf("ft_calculate_push_new_attack\n");
	//i change strategy and i will not attack the closest enemy
	//the closest enemy to me not the closest to my team member
	//i will scan the board from the middle to the sides
	//so fisrt attack the one in middle then go to sides
	int	enemy_x;
	int	enemy_y;
	int	enemy_team_id;

	enemy_x = -1;
	enemy_y = -1;
	printf("My position : x %d y %d\n", player->pos_x, player->pos_y);
	if (ft_player_surround_enemy_from_one_side_and_other_side_free(player, msg))
	{
		//will return x y of the free side 
	 	printf("Attack free side top[%d] right[%d] btm[%d] left[%d]\n", msg->sides[0], msg->sides[1], msg->sides[2], msg->sides[3]);
		int i = 0;
		while (i < 4)
		{
			if (msg->sides[i])
				printf("side i [%d] x [%d] y [%d]\n", i, msg->x_y_sides[i][0], msg->x_y_sides[i][1]);
			i++;
		}
	}
	else
	{
		if (ft_scan_the_board_and_get_x_y_of_enemy_to_attack(player, &enemy_x, &enemy_y, &enemy_team_id) == -1)
		{
			printf("no enemy found\n");
			return (0);//no enemy_found
		}
		printf("Enemy found : pos : x %d , y %d board [%d]\n", enemy_x, enemy_y, player->game->board[enemy_y][enemy_x]);
		msg->x_attack = enemy_x;
		msg->y_attack = enemy_y;
		msg->defence_flag = 0;
	}

	return (ft_push_message_to_queue(player, msg));
	
}


