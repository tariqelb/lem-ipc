#include "./lemipc.h"

int	main(int ac, char **av)
{
	t_player	player;

	if (ac != 2)
	{
		write(2, "Lemipc : Missing player team\n", 29);
		write(2, "Usage: ./lemipc [1 - N]\n", 24);
		return (1);
	}
	player.team_id = ft_get_team(av[1]);
	if (player.team_id == 0)
		return (1);
	//Create shared memory segment for game board 
	//Attach board to shared memory , first player
	//Get access to shared memory for other players
	if (ft_create_shared_memory(&player))
		return (1);
	
	//Implement semaphore system for synchronization
	if (ft_create_semaphore(&player))
	{
		//this decrease needs a lot of checks
		//team adjustment also needed
		player.game->total_players--;
		//check for nbr of player before destroy
		if (player.game->total_players == 0)
			ft_remove_shared_memory(&player);	
		return (1);
	}
	//Set up message queues for inter-process communication
	if (ft_create_message_queue(&player))
	{
		player.game->total_players--;
		if (player.game->total_players == 0)
		{
			ft_destroy_semaphore(&player);
			ft_remove_shared_memory(&player);
			return (1);
		}
	}
	//Turn game to active state
	//ft_active_the_game(&player);
	printf("Game reach this point %d\n", player.game->total_players);
	sleep(20);
	//--------------------------
	//Player dead or game end
	//this decrease needs a lot of checks
	//team adjustment also needed
	player.game->total_players--;
	if (player.game->total_players == 0)
	{
		//check for last player before destroy
		ft_destroy_message_queue(&player);
		//Destroy semaphore
		ft_destroy_semaphore(&player);
		//Destroy shared memory
		ft_remove_shared_memory(&player);
	}
	return (0);
}
