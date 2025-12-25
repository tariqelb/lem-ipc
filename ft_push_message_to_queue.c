#include "./lemipc.h"

int	ft_push_message_to_queue(t_player *player, t_message_queue *msg)
{
	int	status;

	msg->team_id = player->team_id;
	msg->mtype = player->team_id;
	msg->nbr_team_member = player->player_id;
	status = msgsnd(player->msqid, msg, sizeof(*msg) - sizeof(long), 0);
	return (status);
}
