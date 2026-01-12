#include "./lemipc.h"

int	ft_get_resouces(t_player *player)
{
	//initialize semaphore locks
	ft_initialize_semaphore_struct(player);

	//Implement semaphore system for synchronization
	if (ft_create_semaphore(player))
	{
		return (1);
	}
	//Create shared memory segment for game board
	//Attach board to shared memory , first player
	//Get access to shared memory for other players
	if (ft_create_shared_memory(player))
	{
		ft_exit_from_game(player, 1);
		return (1);
	}
	//Set up message queues for inter-process communication
	if (ft_create_message_queue(player))
	{
		ft_exit_from_game(player, 2);
		return (1);
	}
	//Turn game to active state
	if (ft_active_the_game(player) == 0)
	{
		ft_exit_from_game(player, 3);
		return (1);
	}
	return (0);
}
