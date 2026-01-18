#include "./lemipc.h"

int	ft_calculate_push_new_attack(t_player *player, t_message_queue *msg)
{
	ft_putstr("ft_calculate_push_new_attack\n");
	int	enemy_x;
	int	enemy_y;
	int	enemy_team_id;

	enemy_x = -1;
	enemy_y = -1;

	if (ft_scan_the_board_and_get_x_y_of_enemy_to_attack(player, &enemy_x, &enemy_y, &enemy_team_id) == -1)
	{
		return (0);//no enemy_found
	}
	int selected_side = ft_new_enemy_found_select_best_side_to_attack(player, enemy_x, enemy_y, enemy_team_id);
	if (selected_side >= 0)
	{
		//after find an enemy check if its surrounded from one side and other is free , then set flag to 4 and add x_defence/y_defence
		//return 0-to-3 top-right-bottom-left , the free side that should attacked
		//-1 if not surrounded from any side by enemy (if enemy surrounded by the same team member belong to , its not considered as surrounded)
		int x = 0;
		int y = 0;
		if (selected_side == 0)
			y = -1;
		else if (selected_side == 1)
			x = 1;
		else if (selected_side == 2)
			y = 1;
		else if (selected_side == 3)
			x = -1;
		msg->x_defence = enemy_x + x;
		msg->y_defence = enemy_y + y;
		msg->x_player = enemy_x + (x * -1);
		msg->y_player = enemy_y + (y * -1);
		msg->x_attack = enemy_x;
		msg->y_attack = enemy_y;
		msg->defence_flag = 4;
	}
	else
	{
		msg->x_defence = -1;
		msg->y_defence = -1;
		msg->x_player = -1;
		msg->y_player = -1;
		msg->x_attack = enemy_x;
		msg->y_attack = enemy_y;
		msg->defence_flag = 0;
	}

	return (ft_push_message_to_queue(player, msg));
	//ft_push_message_to_queue(player, msg);
	//return (0);
	
}


