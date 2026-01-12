#include "./lemipc.h"

int     ft_get_message_from_message_queue(t_player *player, t_message_queue *msg)
{
	printf("ft_get_message_from_message_queue\n");
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
	printf("msg flag = [%d]\n", msg->defence_flag);
        return (0);
}
