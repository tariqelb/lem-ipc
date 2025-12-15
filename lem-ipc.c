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
	//initialize semaphore locks
	ft_initialize_semaphore_struct(&player);
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
		ft_exit_from_game(&player, 1);
		return (1);
	}
	//Set up message queues for inter-process communication
	if (ft_create_message_queue(&player))
	{
		ft_exit_from_game(&player, 2);
		return (1);
	}
	//allocate memory for player board
	//if (ft_allocate_memory_for_board(&player))
	//{
	//decallocate memory on exit
	//	ft_exit_from_game(N);
	//}
	//Turn game to active state
	if (ft_active_the_game(&player) == 0)
		ft_exit_from_game(&player, 3);
	while (ft_is_the_game_active(&player) == 0)
	{
		//0 mean game not reach minimum nbr of player and teams

		printf("Game is waiting state, players nbr is %d\n", player.game->total_players);
		sleep(5);
	}
	printf("Game starter, players nbr is %d\n", player.game->total_players);
	while (ft_get_into_board(&player))
	{
		printf("Place is full , x = %d , y = %d\n", player.pos_x, player.pos_y);	
		sleep(4);
		if (player.game->game_active == 0)
			break;
	}
	printf("Player get into board : team id %d\n", player.team_id);
	printf("Player position x = %d , y = %d\n", player.pos_x, player.pos_y);
	
	while (player.game->game_active == 1 && player.died == 0)
	{
		//player make move, attack , defend , escape
		if (ft_attack_defend_escape_moves(&player) == 1)
			break;
		sleep(5);
		//temprorary break
		break;
	}
	sleep(20);
	//--------------------------
	//Player dead or game end
	//this decrease needs a lot of checks
	//team adjustment also needed
	ft_exit_from_game(&player, 3);
	return (0);
}
