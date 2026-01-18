#include "./lemipc.h"

int	ft_exit_from_game(t_player *player, int flag)
{
	ft_putstr("ft_exit_from_game");
	//check if last player before destroy resources
	//team ajustement needed here
	//if (player->died == 0 || player->game->game_active == 0)
	//{
	//}
	ft_leave_the_board(player);

	if (player->game->total_players <= 0)
	{
		//check for last player before destroy
		if (flag >= 3)
			ft_destroy_message_queue(player);
		//Destroy shared memory
		if (flag >= 2)
			ft_remove_shared_memory(player);
		//Destroy semaphore
		if (flag >= 1)
			ft_destroy_semaphore(player);
	}
	else 
	{
	 	//leave resource (shared memory)
	 	shmdt(player->game);
	}
	write(1, "Lemipc: Player exit from the game\n", 34);
	return (0);
}
