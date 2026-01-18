#include "./lemipc.h"

int	ft_create_message_queue(t_player *player)
{
	//ft_putstr("ft_create_message_queue\n");
	semop(player->semid, &player->lock_op, 1);
	// 1. Create message queue (first player)
	player->msqid = msgget(MSG_KEY, IPC_CREAT | IPC_EXCL | 0666);
	if (player->msqid != -1)
	{
		write(1, "Lemipc: Create message queue\n", 29);
		semop(player->semid, &player->unlock_op, 1);
		return (0);
	}
	if (errno == EEXIST)
	{
		player->msqid = msgget(MSG_KEY, 0666);
		if (player->semid == -1)
		{
			write(2, "Lemipc: Fail attaching to existing message queue\n", 49);
			semop(player->semid, &player->unlock_op, 1);
			return (1);
		}
		write(1, "Lemipc: Player attached to message queue\n", 41);
		semop(player->semid, &player->unlock_op, 1);
		return (0);
	}
	
	write(2, "Lemipc: Error create/attach message queue\n", 42);
	semop(player->semid, &player->unlock_op, 1);
	return (1);
	// 3. Send messages with appropriate mtype
	//msg.mtype = target_team;
	// 4. Receive messages for your team
	//msgrcv(msqid, &msg, size, MY_TEAM_ID, 0);	
}

int	ft_destroy_message_queue(t_player *player)
{
	//ft_putstr("ft_destroy_message_queue\n");
	int	status;

	status = msgctl(player->msqid, IPC_RMID, NULL);
	if (status == -1)
		write(2, "Lemipc: Error destroying message queue\n", 39);
	else
		write(1, "Lemipc: Message queue destroyed\n", 32);
	return (status);
}
