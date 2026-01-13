#include "./lemipc.h"

int	ft_push_message_to_queue(t_player *player, t_message_queue *msg)
{
	printf("ft_push_message_to_queue : flag = [%d]\n", msg->defence_flag);
	printf("player pos x,y[%d, %d] team id + 1 [%d]\n", player->pos_x, player->pos_y, player->team_id + 1);
	printf("data msg attack [%d][%d] defence [%d][%d] player [%d][%d]\n" , msg->x_attack, msg->y_attack, msg->x_defence , msg->y_defence, msg->x_player, msg->y_player);
	int	status;


	msg->team_id = player->team_id;
	msg->mtype = player->team_id;
	msg->nbr_team_member = player->player_id;
	status = msgsnd(player->msqid, msg, sizeof(*msg) - sizeof(long), 0);
	return (status);
}
