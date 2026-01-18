#include "./lemipc.h"

int	ft_check_if_attack_position_still_valid_and_free(t_player *player, t_message_queue *msg)
{
	ft_putstr("ft_check_if_attack_position_still_valid_and_free\n");
	int player_pos = -1;
	int enemy_pos = -1;
	int free_pos = -1;

	if (msg->x_player < BOARD_X_LEN && msg->y_player < BOARD_Y_LEN)
		player_pos = player->game->board[msg->y_player][msg->x_player];
	if (msg->x_attack < BOARD_X_LEN && msg->y_attack < BOARD_Y_LEN)
		enemy_pos = player->game->board[msg->y_attack][msg->x_attack];
	if (msg->x_defence < BOARD_X_LEN && msg->y_defence < BOARD_Y_LEN)
		free_pos = player->game->board[msg->y_defence][msg->x_defence];
	//return 1 attack stil valid but not current player who surround enemy
	//return 2 valid and current player surround enemy from one side
	//return 3 just an enemy exist in position 

	if (msg->defence_flag == 4)
	{
		if (player_pos > 0 && enemy_pos > 0 && player_pos != enemy_pos && enemy_pos != player->team_id + 1 && free_pos == 0)
		{
			//check if current player how announce the message
			if (player->pos_x == msg->x_player && player->pos_y == msg->y_player)
				return (2);
			if (player->team_id + 1 == player_pos)//team member how surround enemy
				return (1);
		}
	}
	return (0);
}
